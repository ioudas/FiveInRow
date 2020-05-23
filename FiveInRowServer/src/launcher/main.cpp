#include <csignal>
#include <cstdlib>

#include "Repository.h"
#include "Server.h"
#include "GameEngine.h"
#include "GameInterface.h"
#include "WinningConditions.h"
#include "Exceptions/ServerException.cpp"

#define DEFAULT_PORT 8888;

int TryParsePort(char *firstArg);

int main(int argc, char *argv[]) {

    //manual IoC :/
    Repository repository;
    Server server;
    WinningConditions winningConditions;
    BoardFormatter boardFormatter;
    GameInterface gameInterface(server, repository, boardFormatter);
    GameEngine game(repository, server, gameInterface, winningConditions);

    int port = DEFAULT_PORT;
    if(argc < 2)
        std::cout << "To change the default port use syntax: \"server.exe <port>\"\n";
    else
        port = TryParsePort(argv[1]);

    try {
        game.Start(port);

    } catch (ServerException &e) {
        perror(e.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int TryParsePort(char *firstArg) {
    try {
        return std::stoi(firstArg);
    } catch (std::exception const &e) {
        perror(("Invalid port " + std::string(firstArg)).c_str());
        exit(EXIT_FAILURE);
    }

}

