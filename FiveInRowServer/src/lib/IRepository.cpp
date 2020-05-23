//
// Created by ioudas on 5/23/2020.
//

#include "Repository.h"
#include <algorithm>
#include "IRepository.h"

GameState IRepository::GetGameState() const {
    return Repository::gameState;
}

void IRepository::AddPlayerTurn(int playerId, int columnNum) {
    int lastRow = Repository::GetLastRow(Repository::gameState, columnNum - 1);
    auto symbol = GetPlayerSymbol(playerId);
    Repository::gameState.Board[columnNum - 1][lastRow] = symbol;
}

Player IRepository::GetOpponent(int playerId) {
    Player &opponent = *std::find_if(Repository::gameState.Players.begin(), Repository::gameState.Players.end(),
                                     [playerId](const Player p) { return p.Id != playerId; });
    return opponent;
}

void IRepository::SetActingPlayerId(int playerId) {
    Repository::gameState.ActingPlayerId = playerId;
}

int IRepository::GetActingPlayerId() {
    return Repository::gameState.ActingPlayerId;
}

void IRepository::AddPlayer(int playerId) {
    Player player = Player(playerId);

    if(GetPlayerCount() == 0) {
        player.Symbol = 'x';
    } else player.Symbol = 'o';

    Repository::gameState.Players.emplace_back(player);
}

void IRepository::SetPlayerName(int playerId, std::string playerName) {
    Player& player = GetPlayer(playerId);
    player.PlayerName = playerName;
}

int IRepository::GetPlayerCount() {
    return Repository::gameState.Players.size();
}

Player& IRepository::GetPlayer(int playerId) {
    return *std::find_if(Repository::gameState.Players.begin(), Repository::gameState.Players.end(),
                         [playerId](const Player p) { return p.Id == playerId; } );
}

std::vector<Player> IRepository::GetPlayers() {
    return Repository::gameState.Players;
}

void IRepository::ClearState() {
    Repository::gameState.Players.clear();
    Repository::gameState = GameState();
}

char IRepository::GetPlayerSymbol(int playerId) {
    return GetPlayer(playerId).Symbol;
}