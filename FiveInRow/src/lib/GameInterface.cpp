
#include "GameInterface.h"

void GameInterface::NotifyGameAbandoned(int winnerPlayerId, string playerLeftName) {
    auto message = string_format("Congratulations! You have won because player %s cowardly left the game.\r", playerLeftName.c_str());
    server.SendMessageToPlayer(MessageType::GameOver, winnerPlayerId, message);
}

void GameInterface::NotifyWelcome(int playerId, string playerName) {
    auto message = string_format("Welcome %s", playerName.c_str());
    server.SendMessageToPlayer(MessageType::Information, playerId, message);
}

void GameInterface::NotifyWaitForOpponent(int playerId) {
    server.SendMessageToPlayer(MessageType::Information, playerId, "Please wait for the other player to connect\n");
}

void GameInterface::NotifyOpponentConnected(int playerId, string opponentName) {
    auto message = string_format("Player %s connected\n", opponentName.c_str());
    server.SendMessageToPlayer(MessageType::Information, playerId, message);
}

void GameInterface::NotifyGameStarting() {
    server.BroadCastMessage(MessageType::Information, "The game is starting!\n");
}

void GameInterface::SendBoardState() {
    auto gameState = repository.GetGameState();
    auto legend = boardFormatter.GetLegend(gameState);
    auto board = boardFormatter.GetAscii(gameState);
    auto message = legend + board;
    server.BroadCastMessage(MessageType::Information, message);
}

void GameInterface::NotifyWaitForOpponentTurn(int playerId, string opponentName) {
    auto message = string_format("Please wait for %s's turn\n", opponentName.c_str());
    server.SendMessageToPlayer(MessageType::Information, playerId, message);
}

void GameInterface::NotifyPlayerTurn(int playerId) {
    server.SendMessageToPlayer(MessageType::InputRequest, playerId, "It's your turn! Please enter column number (1-9): ");
}

void GameInterface::RetryInvalidInput(int playerId) {
    server.SendMessageToPlayer(MessageType::InputRequest, playerId, "Invalid input. Please enter column number (1-9): ");
}

void GameInterface::NotifyGameWon(string winnerPlayerName) {
    auto message = string_format("Player %s' won!", winnerPlayerName.c_str());
    server.BroadCastMessage(MessageType::GameOver, message);
}

