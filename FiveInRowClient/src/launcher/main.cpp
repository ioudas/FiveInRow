#define PORT 8888
#define LOCALHOST "127.0.0.1"

#include "Client.h"
#include "Game.h"
#include "Exceptions/ClientException.cpp"

int main(int argc, char const *argv[])
{
    Client client;
    Game game(client);
    try {
        game.Start(LOCALHOST, PORT);

    } catch (ClientException& e) {
        perror(e.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


