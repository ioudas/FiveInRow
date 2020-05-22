#ifndef FIVEINROWCLIENT_GAME_H
#define FIVEINROWCLIENT_GAME_H

#include "Client.h"

class Game {
public:
    void Start(std::string hostname, int port);
    Game(Client &client): client(client) {}

private:
    Client &client;

    std::string GetPlayerName() const;

    void ProcessResponse(Response &response);

    void Pause();
};


#endif //FIVEINROWCLIENT_GAME_H
