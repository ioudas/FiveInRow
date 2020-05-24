#ifndef FIVEINROWRUN_GAMEINTERFACE_H
#define FIVEINROWRUN_GAMEINTERFACE_H

#include "Server.h"
#include "Repository.h"
#include "BoardFormatter.h"
#include <string>

using std::string;

class IGameInterface {
public:
    virtual void NotifyWelcome(int playerId, string playerName) = 0;
    virtual void NotifyWaitForOpponent(int playerId) = 0;
    virtual void NotifyOpponentConnected(int playerId, string opponentName) = 0;
    virtual void NotifyGameStarting() = 0;
    virtual void SendBoardState() = 0;
    virtual void NotifyWaitForOpponentTurn(int playerId, string opponentName) = 0;
    virtual void NotifyPlayerTurn(int playerId) = 0;
    virtual void RetryInvalidInput(int playerId) = 0;
    virtual void RetryInputOutOfBounds(int playerId) = 0;
    virtual void NotifyGameWon(string winnerPlayerName) = 0;
    virtual void NotifyGameAbandoned(int winnerPlayerId, string playerLeftName) = 0;
};

class GameInterface : public IGameInterface{
private:
    Server &server;
    Repository &repository;
    BoardFormatter &boardFormatter;

public:
    GameInterface(Server &server, Repository &repository, BoardFormatter &boardFormatter) :
            server(server),
            repository(repository),
            boardFormatter(boardFormatter) {};

    void NotifyWelcome(int playerId, string playerName) override;
    void NotifyWaitForOpponent(int playerId) override;
    void NotifyOpponentConnected(int playerId, string opponentName) override;
    void NotifyGameStarting() override;
    void SendBoardState() override;
    void NotifyWaitForOpponentTurn(int playerId, string opponentName) override;
    void NotifyPlayerTurn(int playerId) override;
    void RetryInvalidInput(int playerId) override;
    void RetryInputOutOfBounds(int playerId) override;
    void NotifyGameWon(string winnerPlayerName) override;
    void NotifyGameAbandoned(int winnerPlayerId, string playerLeftName) override;
};

#endif //FIVEINROWRUN_GAMEINTERFACE_H
