#include "Exceptions/ServerException.cpp"
#include "Server.h"
#include "ProtocolHelper.h"

void Server::Start(int port) {
    sockaddr_in address = GetAddress(port);

    socketDescriptor = OpenSocket(port, address);

    StartListener(address);
}

void Server::SendMessageToPlayer(MessageType messageType, int playerId, std::string message) {
    const char *payload = ProtocolHelper::Serialize(messageType, message);
    SOCKET clientSocket = clientSockets[playerId];
    printf("Sending message to PlayerId: %d Payload: %s\n", playerId, payload);
    if (send(clientSocket, payload, strlen(payload), 0) != strlen(payload)) {
        int error = -1;
#ifdef _WIN32
        error = WSAGetLastError();
#endif
        throw ServerException("Could not send activity: code " + std::to_string(error));
    }
}

void Server::BroadCastMessage(MessageType messageType, std::string message) {
    const char *payload = ProtocolHelper::Serialize(messageType, message);
    for (int i = 0; i < MAX_CLIENTS; ++i) {
        auto clientSocket = clientSockets[i];
        printf("Sending message to PlayerId: %d Payload: %s\n", i, payload);
        if (send(clientSocket, payload, strlen(payload), 0) != strlen(payload)) {
            int error = -1;
#ifdef _WIN32
            error = WSAGetLastError();
#endif
            throw ServerException("Could not send activity: code " + std::to_string(error));
        }
    }

}

Server::~Server() {
    for (const int socket: clientSockets) {
        CloseSocket(socket);
    }
    CloseSocket(socketDescriptor);
    WSACleanup();
    printf("Server stopped\n");
}

SOCKET Server::OpenSocket(int port, const sockaddr_in &address) {
    InitSocket();

    if ((socketDescriptor = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        throw ServerException("Failed to create socket!");
    }

    int optionValue = 1;
    if (setsockopt(socketDescriptor, SOL_SOCKET, SO_REUSEADDR, (char *) &optionValue, sizeof(optionValue)) < 0) {
        throw ServerException("Failed to set socket options!");
    }


    int bindRes = bind(socketDescriptor, (struct sockaddr *) &address, sizeof(address));
    if (bindRes < 0) {
        throw ServerException("Could not bind on: " + std::to_string(port));
    }
    printf("Listening on port %d \n", port);

    if (listen(socketDescriptor, 3) < 0) {
        throw ServerException("Could not start server");
    }

    return socketDescriptor;
}

void Server::StartListener(const sockaddr_in &address) {
    int addrlen, activity, i, valread;
    fd_set readfds;
    int max_sd;
    while (1) {
        FD_ZERO(&readfds);
        FD_SET(socketDescriptor, &readfds);
        max_sd = socketDescriptor;

        //add child sockets to set
        for (const int sd: clientSockets) {
            //if valid socket descriptor then add to read list
            if (sd > 0)
                FD_SET(sd, &readfds);

            //highest file descriptor number, need it for the select function on linux
            if (sd > max_sd)
                max_sd = sd;
        }

        //wait for an activity on one of the sockets , timeout is NULL ,
        //so wait indefinitely
        activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);

        if ((activity < 0) && (errno != EINTR)) {
            int error = errno;
#ifdef _WIN32
            error = WSAGetLastError();
#endif
            throw ServerException("Could not read activity from socket: code " + std::to_string(error));
        }

        //If something happened on the master socket, then its an incoming connection
        if (FD_ISSET(socketDescriptor, &readfds)) {
            addrlen = AcceptConnection(address);

            continue;
        }

        //else its some IO operation on one of the connected sockets
        for (int i = 0; i < MAX_CLIENTS; i++) {
            SOCKET sd = clientSockets[i];
            if (FD_ISSET(sd, &readfds)) {
                char buffer[1025];
                if ((valread = recv(sd, buffer, 1024, 0)) < 1) {
                    OnClientDisconnected(address, addrlen, i, sd);

                } else {
                    OnClientMessage(valread, i, buffer);
                }
            }
        }
    }
}

void Server::OnClientMessage(int valread, int i, char *buffer) {
    //set the string terminating NULL byte on the end of the data read
    buffer[valread] = '\0';
    printf("Received message: %s \n", buffer);
    std::string message = std::string(buffer);
    if (!message.empty())
        onPlayerInput(i, message);
}

void Server::OnClientDisconnected(const sockaddr_in &address, int &addrlen, int i, SOCKET sd) {
    //Print host info
    getpeername(sd, (struct sockaddr *) &address, (socklen_t *) &addrlen);
    printf("Host disconnected , ip %s , port %d \n",
           inet_ntoa(address.sin_addr), ntohs(address.sin_port));

    //Close the socket and mark as 0 in list for reuse
    CloseSocket(sd);
    clientSockets[i] = 0;

    //Trigger callback
    onPlayerLeft(i);
}

int Server::AcceptConnection(const sockaddr_in &address) {
    int new_socket, addrlen = sizeof(address);
    if ((new_socket = accept(socketDescriptor, (struct sockaddr *) &address, (socklen_t *) &addrlen)) ==
        INVALID_SOCKET) {
        int error = new_socket;
#ifdef _WIN32
        error = WSAGetLastError();
#endif
        throw ServerException("Could not accept connection: code " + std::to_string(error));
    }

    //inform user of socket number - used in send and receive commands
    printf("New connection , socket fd is %d , ip is : %s , port : %d", new_socket,
           inet_ntoa(address.sin_addr), ntohs(address.sin_port));

    //add new socket to array of sockets
    for (int i = 0; i < sizeof(clientSockets); i++) {
        //if position is empty
        if (clientSockets[i] == 0) {
            clientSockets[i] = new_socket;
            printf("Adding to list of sockets as %d\n", i);
            //Trigger callback
            PlayerConnected(i);

            break;
        }
    }

    return addrlen;
}

sockaddr_in Server::GetAddress(int port) const {
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    return address;
}

int Server::InitSocket(void) {
#ifdef _WIN32
    WSADATA wsa_data;
    return WSAStartup(MAKEWORD(2, 2), &wsa_data);
#else
    return 0;
#endif
}

int Server::CloseSocket(SOCKET sock) {
    int status = 0;
#ifdef _WIN32
    status = shutdown(sock, SD_BOTH);
    if (status == 0) { status = closesocket(sock); }
#else
    status = shutdown(sock, SHUT_RDWR);
if (status == 0) { status = close(sock); }
#endif

    return status;

}


