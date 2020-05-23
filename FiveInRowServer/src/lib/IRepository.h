//
// Created by ioudas on 5/23/2020.
//

#ifndef FIVEINROWSERVER_IREPOSITORY_H
#define FIVEINROWSERVER_IREPOSITORY_H


#include <string>
#include <array>
#include "Models/GameState.cpp"

class IRepository {

public:
    GameState GetGameState() const;

    void AddPlayerTurn(int playerId, int columnNum);

    IRepository() : gameState() {}

    Player GetOpponent(int playerId);

    void SetActingPlayerId(int playerId);

    int GetActingPlayerId();

    void AddPlayer(int playerId);

    void SetPlayerName(int playerId, std::string playerName);

    int GetPlayerCount();

    Player& GetPlayer(int playerId);

    std::vector<Player> GetPlayers();

    void ClearState();

    char GetPlayerSymbol(int playerId);
};


#endif //FIVEINROWSERVER_IREPOSITORY_H
