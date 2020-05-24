#define DEFAULT_PORT 8888
#define DEFAULT_HOST "127.0.0.1"

#include "Client.h"
#include "Game.h"
#include "Exceptions/ClientException.cpp"

using std::string;
using std::tuple;

tuple<string, int> TryParseUri(const char *firstArg);

int main(int argc, char const *argv[])
{
    Client client;
    Game game(client);

    int port = DEFAULT_PORT;
    string hostname = DEFAULT_HOST;
    if(argc < 2)
        std::cout << "To change the default server uri use syntax: \"client.exe <hostname>:<port>\"\n";
    else
    {
        auto [customHostname, customPort] = TryParseUri(argv[1]);
        hostname = customHostname;
        port = customPort;
    }
    try {
        game.Start(hostname, port);

    } catch (ClientException& e) {
        perror(e.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


tuple<string, int> TryParseUri(const char *firstArg) {
    auto uri = string(firstArg);

    auto colonPos = uri.find(':');
    if(colonPos == string::npos || colonPos == 0 || colonPos == uri.size() || uri.size() < 3) {
        perror(("Invalid argument " + string(firstArg)).c_str());
        exit(EXIT_FAILURE);
    }

    string hostname = uri.substr(0, uri.find(':'));
    string portText = uri.substr(uri.find(':') + 1, uri.length());
    try {
        auto port = std::stoi(portText);
        return {hostname, port};
    } catch (std::exception const &e) {
        perror(("Invalid port " + string(portText)).c_str());
        exit(EXIT_FAILURE);
    }

}
