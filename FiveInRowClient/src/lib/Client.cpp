#include "Client.h"
#include "Exceptions/ClientException.cpp"
#include "ProtocolHelper.h"

void Client::Connect(std::string hostname, int port) {
    printf("Connecting to %s:%d\n", hostname.c_str(), port);

    InitSocket();

    if ((socketDescriptor = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        throw ClientException("Socket creation error");
    }

    sockaddr_in address = GetAddress(port);
    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, hostname.c_str(), &address.sin_addr) <= 0) {
        throw ClientException("Invalid address/ Address not supported");
    }

    if (connect(socketDescriptor, (struct sockaddr *) &address, sizeof(address)) < 0) {
        throw ClientException("Connection Failed! Url: " + hostname + ":" + std::to_string(port));
    }

    printf("Connected to %s:%d\n", hostname.c_str(), port);

}

Response Client::Login(std::string playerName) {
    printf("Logging in as %s\n", playerName.c_str());
    return SendRequest(playerName);
}

Response Client::SendRequest(std::string message) {
    const char *msg = message.c_str();
    send(socketDescriptor, msg, strlen(msg), 0);

    return WaitForServerResponse();
}

Response Client::WaitForServerResponse() const {
    char recvbuffer[1024] = {0};
    int recvResult = recv(socketDescriptor, recvbuffer, sizeof(recvbuffer), 0);
    if (recvResult > 0) {
    } else if (recvResult == SOCKET_ERROR) {
        int error = -1;
#ifdef _WIN32
        error = WSAGetLastError();
#endif
        throw ClientException("Connection closed with code :" + std::to_string(error));
    } else
        throw ClientException("Connection closed");

    return ProtocolHelper::Deserialize(recvbuffer);
}

Client::~Client() {
    CloseSocket(socketDescriptor);
    WSACleanup();
}

int Client::InitSocket(void) {
#ifdef _WIN32
    WSADATA wsa_data;
    return WSAStartup(MAKEWORD(2, 2), &wsa_data);
#else
    return 0;
#endif
}

int Client::CloseSocket(SOCKET sock) {
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

sockaddr_in Client::GetAddress(int port) const {
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    return address;
}


