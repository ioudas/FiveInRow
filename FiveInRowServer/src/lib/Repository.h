#ifndef FIVEINROW_REPOSITORY_H
#define FIVEINROW_REPOSITORY_H

#include <Models/Coords.h>
#include "Models/GameState.h"
#include <string>
#include <array>


class IRepository {
public:
    virtual GameState GetGameState() const = 0;

    virtual void SetActingPlayerId(int playerId) = 0;

    virtual int GetActingPlayerId() = 0;

    virtual bool TryAddPlayerTurn(int playerId, int columnNum, Coords &coords) = 0;

    virtual void AddPlayer(int playerId) = 0;

    virtual void SetPlayerName(int playerId, std::string playerName) = 0;

    virtual int GetPlayerCount() = 0;

    virtual Player& GetPlayer(int playerId) = 0;

    virtual std::vector<Player> GetPlayers() = 0;

    virtual Player& GetOpponent(int playerId) = 0;

    virtual char GetPlayerSymbol(int playerId) = 0;

    virtual void ClearState() = 0;
};


class Repository : public IRepository{
private:
    GameState gameState;
    int GetLastRow(const GameState &gameState, int columnIdx);
public:
    Repository() : gameState() { }

    GameState GetGameState() const override;

    void SetActingPlayerId(int playerId) override;

    int GetActingPlayerId() override;

    bool TryAddPlayerTurn(int playerId, int columnNum, Coords &coords) override;

    void AddPlayer(int playerId) override;

    void SetPlayerName(int playerId, std::string playerName) override;

    int GetPlayerCount() override;

    Player& GetPlayer(int playerId) override;

    std::vector<Player> GetPlayers() override;

    Player& GetOpponent(int playerId) override;

    char GetPlayerSymbol(int playerId) override;

    void ClearState() override;
};

#endif //FIVEINROW_REPOSITORY_H
