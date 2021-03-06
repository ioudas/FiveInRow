#include "GameEngine.h"

void GameEngine::Start(int port) {
    server.SetOnPlayerConnected([this](int playerId) { this->PlayerConnected(playerId); });
    server.SetOnPlayerLeft([this](int playerId) { this->PlayerLeft(playerId); });
    server.SetOnPlayerInput([this](int playerId, string input) { this->PlayerInput(playerId, input); });

    server.Start(port);
}

void GameEngine::PlayerConnected(int playerId) {
    repository.AddPlayer(playerId);
}

void GameEngine::PlayerLeft(int playerId) {
    if (repository.GetPlayerCount() > 1) {
        auto player = repository.GetPlayer(playerId);
        auto recipient = repository.GetOpponent(playerId);
        gameInterface.NotifyGameAbandoned(recipient.Id, player.PlayerName);
    }
    repository.ClearState();
}

void GameEngine::PlayerInput(int playerId, string input) {

    if(repository.GetPlayerCount() == 0) {
        printf("ERROR: No players connected");
        return;
    }

    Player player = repository.GetPlayer(playerId);

    if(player.PlayerName.empty()) {
        HandleLogin(playerId, input);

        return;
    }

    if(repository.GetPlayerCount() != 2) {
        printf("ERROR: Not enough players: %d", repository.GetPlayerCount());
        return;
    }

    if (repository.GetActingPlayerId() != playerId) {
        printf("ERROR: Not player's turn: %s", player.PlayerName.c_str());
        return;
    }

    if (input.length() != 1 || !isdigit(input.at(0))) {
        printf("ERROR: Invalid input: %s", input.c_str());
        gameInterface.RetryInvalidInput(playerId);
        return;
    }

    int columnNumber = input.at(0) - '0'; //convert char to int
    if(columnNumber < 1 || columnNumber > 9) {
        printf("ERROR: Invalid input: %s", input.c_str());
        gameInterface.RetryInvalidInput(playerId);
        return;
    }

    Coords coords(0, 0);
    if(!repository.TryAddPlayerTurn(playerId, columnNumber, coords)) {
        printf("ERROR: Move is out of bounds: %s", input.c_str());
        gameInterface.RetryInputOutOfBounds(playerId);
        return;
    }
    gameInterface.SendBoardState();

    if (winningConditions.IsGameWon(repository.GetGameState(), coords))
    {
        HandleGameWon(player.PlayerName);

        return;
    }

    auto otherPlayer = repository.GetOpponent(playerId);
    gameInterface.NotifyWaitForOpponentTurn(playerId, otherPlayer.PlayerName);
    repository.SetActingPlayerId(otherPlayer.Id);
    gameInterface.NotifyPlayerTurn(otherPlayer.Id);

}

void GameEngine::HandleLogin(int playerId, string input) {
    repository.SetPlayerName(playerId, input);
    gameInterface.NotifyWelcome(playerId, input);

    if(repository.GetPlayerCount() == 1) {
        gameInterface.NotifyWaitForOpponent(playerId);

        return;
    }

    //Notify other player that the opponent just connected
    auto otherPlayer = repository.GetOpponent(playerId);
    gameInterface.NotifyOpponentConnected(otherPlayer.Id, input);

    StartNewGame();
}

void GameEngine::StartNewGame() {
    gameInterface.NotifyGameStarting();
    gameInterface.SendBoardState();

    //Shuffle starting player
    auto players = repository.GetPlayers();
    unsigned int index = randomProvider.Next(0, 1);
    auto player = players[index];

    repository.SetActingPlayerId(player.Id);

    gameInterface.NotifyPlayerTurn(player.Id);
    auto otherPlayer = repository.GetOpponent(player.Id);
    gameInterface.NotifyWaitForOpponentTurn(otherPlayer.Id, player.PlayerName);
}

void GameEngine::HandleGameWon(string winnerName) const {
    gameInterface.NotifyGameWon(winnerName);
    repository.ClearState();
}
