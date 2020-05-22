#ifndef FIVEINROWCLIENT_CLIENT_H
#define FIVEINROWCLIENT_CLIENT_H

#ifdef _WIN32
/* See http://stackoverflow.com/questions/12765743/getaddrinfo-on-win32 */
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif
#include <winsock2.h>
#include <stdio.h>
#include <ws2tcpip.h>
#include <w32api.h>


#else
/* Assume that any non-Windows platform uses POSIX-style sockets instead. */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>  /* Needed for getaddrinfo() and freeaddrinfo() */
#include <unistd.h> /* Needed for close() */
#endif

#include <cstdio>
#include <unistd.h>
#include <string>
#include <iostream>
#include <functional>
#include "Models/Response.cpp"

class Client {
private:
    SOCKET socketDescriptor = 0;
    sockaddr_in GetAddress(int port) const;
    int InitSocket(void);
    int CloseSocket(SOCKET sock);
public:
    void Connect(std::string hostname, int port);
    Response Login(std::string playerName);
    Response SendRequest(std::string message);
    Response WaitForServerResponse() const;
    ~Client();
};

#endif //FIVEINROWCLIENT_CLIENT_H
