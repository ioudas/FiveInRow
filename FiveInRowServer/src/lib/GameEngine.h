#ifndef FIVEINROW_GAMEENGINE_H
#define FIVEINROW_GAMEENGINE_H

#include "Repository.h"
#include "GameInterface.h"
#include "WinningConditions.h"

#include <string>

using std::string;

class GameEngine {
private:
    Repository &repository;
    WinningConditions &winningConditions;
    GameInterface &gameInterface;
    IServer &server;

    void StartNewGame();

    void HandleLogin(int playerId, string input);

    void HandleGameWon(char winnerSymbol) const;

public:
    GameEngine(Repository &repository,
               Server &server,
               GameInterface &gameInterface,
               WinningConditions &winningConditions) :
            repository(repository),
            gameInterface(gameInterface),
            winningConditions(winningConditions),
            server(server) {};

    void Start(int port);

    void PlayerConnected(int playerId);

    void PlayerLeft(int playerId);

    void PlayerInput(int playerId, string input);
};

#endif //FIVEINROW_GAMEENGINE_H
