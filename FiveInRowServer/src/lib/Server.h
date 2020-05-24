#ifndef FIVEINROW_SERVER_H
#define FIVEINROW_SERVER_H

#include <string>
#include <functional>
#include "Models/MessageType.h"
#ifdef _WIN32
/* See http://stackoverflow.com/questions/12765743/getaddrinfo-on-win32 */
#ifndef _WIN32_WINNT
#endif

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#else
/* Assume that any non-Windows platform uses POSIX-style sockets instead. */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>  /* Needed for getaddrinfo() and freeaddrinfo() */
#include <unistd.h> /* Needed for close() */
#endif

#define MAX_CLIENTS 2

class IServer {
public:
   virtual ~IServer() { };
   virtual void Start(int port) = 0;
   virtual void SendMessageToPlayer(MessageType messageType, int playerId, std::string message) = 0;
   virtual void BroadCastMessage(MessageType messageType, std::string message) = 0;
   virtual void SetOnPlayerConnected(std::function<void(int)> callback) = 0;
   virtual void SetOnPlayerLeft(std::function<void(int)> callback) = 0;
   virtual void SetOnPlayerInput(std::function<void(int, std::string)> callback) = 0;
};

class Server : public IServer {
private:
    SOCKET socketDescriptor, clientSockets[MAX_CLIENTS]{0, 0};
    sockaddr_in GetAddress(int port) const;
    int InitSocket(void);
    int CloseSocket(SOCKET sock);
    SOCKET OpenSocket(int port, const sockaddr_in &address);
    void StartListener(const sockaddr_in &address);
    int AcceptConnection(const sockaddr_in &address);
    void OnClientDisconnected(const sockaddr_in &address, int &addrlen, int i, SOCKET sd);
    void OnClientMessage(int valread, int i, char *buffer);
    std::function<void(int)> onPlayerConnected;
    std::function<void(int)> onPlayerLeft;
    std::function<void(int, std::string)> onPlayerInput;
public:
    ~Server() override;
    void Start(int port) override;
    void SendMessageToPlayer(MessageType messageType, int playerId, std::string message) override;
    void BroadCastMessage(MessageType messageType, std::string message) override;
    void SetOnPlayerConnected(std::function<void(int)> callback) override;
    void SetOnPlayerLeft(std::function<void(int)> callback) override;
    void SetOnPlayerInput(std::function<void(int, std::string)> callback) override;
};

#endif //FIVEINROW_SERVER_H
