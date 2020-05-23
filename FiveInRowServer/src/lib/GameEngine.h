#ifndef FIVEINROW_GAMEENGINE_H
#define FIVEINROW_GAMEENGINE_H

#include "Repository.h"
#include "GameInterface.h"
#include "WinningConditions.h"

#include <string>

using std::string;

class GameEngine {
private:
    IRepository &repository;
    IWinningConditions &winningConditions;
    IGameInterface &gameInterface;
    IServer &server;

    void StartNewGame();

    void HandleLogin(int playerId, string input);

    void HandleGameWon(char winnerSymbol) const;

public:
    GameEngine(IRepository &repository,
               IServer &server,
               IGameInterface &gameInterface,
               IWinningConditions &winningConditions) :
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
