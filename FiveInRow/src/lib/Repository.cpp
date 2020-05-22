#include <algorithm>
#include "Repository.h"

GameState Repository::GetGameState() const {
    return gameState;
}

void Repository::AddPlayerTurn(int playerId, int columnNum) {
    int lastRow = GetLastRow(gameState, columnNum - 1);
    auto symbol = GetPlayerSymbol(playerId);
    gameState.Board[columnNum - 1][lastRow] = symbol;
}

Player Repository::GetOpponent(int playerId) {
    Player &opponent = *std::find_if(gameState.Players.begin(), gameState.Players.end(),
                                     [playerId](const Player p) { return p.Id != playerId; });
    return opponent;
}

void Repository::SetActingPlayerId(int playerId) {
    gameState.ActingPlayerId = playerId;
}

int Repository::GetActingPlayerId() {
    return gameState.ActingPlayerId;
}

void Repository::AddPlayer(int playerId) {
    Player player = Player(playerId);

    if(GetPlayerCount() == 0) {
        player.Symbol = 'x';
    } else player.Symbol = 'o';

    gameState.Players.emplace_back(player);
}

void Repository::SetPlayerName(int playerId, std::string playerName) {
    Player& player = GetPlayer(playerId);
    player.PlayerName = playerName;
}

int Repository::GetPlayerCount() {
    return gameState.Players.size();
}

Player& Repository::GetPlayer(int playerId) {
    return *std::find_if(gameState.Players.begin(), gameState.Players.end(),
                              [playerId](const Player p) { return p.Id == playerId; } );
}

std::vector<Player> Repository::GetPlayers() {
    return gameState.Players;
}

void Repository::ClearState() {
    gameState.Players.clear();
    gameState = GameState();
}

char Repository::GetPlayerSymbol(int playerId) {
    return GetPlayer(playerId).Symbol;
}

int Repository::GetLastRow(const GameState &gameState, int columnIdx) {
    int lastRow = 0;
    auto lastRowIte = std::find_if(gameState.Board[columnIdx].rbegin(), gameState.Board[columnIdx].rend(),
                                   [](const char c) { return c != '\0'; });
    if (lastRowIte != gameState.Board[columnIdx].rend()) {
        lastRow = std::distance(gameState.Board[columnIdx].begin(), lastRowIte.base());
    }
    return lastRow;
}

