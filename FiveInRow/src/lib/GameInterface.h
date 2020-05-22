#ifndef FIVEINROWRUN_GAMEINTERFACE_H
#define FIVEINROWRUN_GAMEINTERFACE_H

#include "Server.h"
#include "Repository.h"
#include "BoardFormatter.h"
#include <string>

using std::string;

class GameInterface {
private:
    Server &server;
    Repository &repository;
    BoardFormatter &boardFormatter;

public:
    GameInterface(Server &server, Repository &repository, BoardFormatter &boardFormatter) :
            server(server),
            repository(repository),
            boardFormatter(boardFormatter) {};

    void NotifyWelcome(int playerId, string playerName);

    void NotifyWaitForOpponent(int playerId);

    void NotifyOpponentConnected(int playerId, string opponentName);

    void NotifyGameStarting();

    void SendBoardState();

    void NotifyWaitForOpponentTurn(int playerId, string opponentName);

    void NotifyPlayerTurn(int playerId);

    void RetryInvalidInput(int playerId);

    void NotifyGameWon(string winnerPlayerName);

    void NotifyGameAbandoned(int winnerPlayerId, string playerLeftName);
};

#endif //FIVEINROWRUN_GAMEINTERFACE_H
