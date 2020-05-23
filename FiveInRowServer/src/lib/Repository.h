#ifndef FIVEINROW_REPOSITORY_H
#define FIVEINROW_REPOSITORY_H

#include "Models/GameState.cpp"
#include <string>
#include <array>

class Repository {
private:
    GameState gameState;
    int GetLastRow(const GameState &gameState, int columnIdx);
public:
    Repository() : gameState() {}

    GameState GetGameState() const;

    void SetActingPlayerId(int playerId);

    int GetActingPlayerId();

    void AddPlayerTurn(int playerId, int columnNum);

    void AddPlayer(int playerId);

    void SetPlayerName(int playerId, std::string playerName);

    int GetPlayerCount();

    Player& GetPlayer(int playerId);

    std::vector<Player> GetPlayers();

    Player GetOpponent(int playerId);

    char GetPlayerSymbol(int playerId);

    void ClearState();

};

#endif //FIVEINROW_REPOSITORY_H
