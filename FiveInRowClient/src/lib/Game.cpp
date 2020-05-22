#include <string>
#include <iostream>
#include "Game.h"

void Game::Start(std::string hostname, int port) {
    std::string playerName = GetPlayerName();
    client.Connect(hostname, port);
    Response response = client.Login(playerName);

    while (response.Type != GameOver) {
        ProcessResponse(response);
    }

    printf(response.Message.c_str());
}

std::string Game::GetPlayerName() const {
    printf("Please enter your name: \n");
    std::string playerName;
    std::getline(std::cin, playerName);

    return playerName;
}

void Game::ProcessResponse(Response &response) {
    printf("%s\n", response.Message.c_str());

    if (response.Type == InputRequest) {
        std::string input;
        std::getline(std::cin, input);
        response = client.SendRequest(input);
        return;
    }

    if (response.Type == Information) {
        response = client.WaitForServerResponse();
    }
}