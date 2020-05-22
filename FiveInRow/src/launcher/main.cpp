#include <csignal>
#include <cstdlib>

#include "Repository.h"
#include "Server.h"
#include "GameEngine.h"
#include "GameInterface.h"
#include "WinningConditions.h"
#include "Exceptions/ServerException.cpp"

int main(int argc, char *argv[]) {

    //manual IoC :/
    Repository repository;
    Server server;
    WinningConditions winningConditions;
    BoardFormatter boardFormatter;
    GameInterface gameInterface(server, repository, boardFormatter);
    GameEngine game(repository, server, gameInterface, winningConditions);

    try {
        game.Start();

    } catch (ServerException &e) {
        perror(e.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

