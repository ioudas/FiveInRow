#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Mocks/ServerMock.h"
#include "Mocks/RepositoryMock.h"
#include "Mocks/BoardFormatterMock.h"
#include "Mocks/WinningConditionsMock.h"
#include "Mocks/GameInterfaceMock.h"
#include "GameEngine.h"
#include "Mocks/RandomProviderMock.h"

using ::testing::Exactly;
using ::testing::Return;
using ::testing::ReturnRef;
using ::testing::SaveArg;
using ::testing::_;

class GameEngineTestSuite : public ::testing::Test {
protected:
    ServerMock serverMock;
    RepositoryMock repositoryMock;
    BoardFormatterMock boardFormatterMock;
    WinningConditionsMock winningConditionsMock;
    GameInterfaceMock gameInterfaceMock;
    RandomProviderMock randomProviderMock;
    GameEngine sut = GameEngine(repositoryMock, serverMock, gameInterfaceMock, winningConditionsMock, randomProviderMock);
    Player player = Player(6);
    Player opponent = Player(16);
    std::vector<Player> players;

    void SetUp() override {
        player.PlayerName = "PLAYER";
        opponent.PlayerName = "OPPONENT";
        players.emplace_back(player);
        players.emplace_back(opponent);

        //setup repository mock
        EXPECT_CALL(repositoryMock, GetPlayer(player.Id)).WillRepeatedly(ReturnRef(player));
        EXPECT_CALL(repositoryMock, GetPlayer(opponent.Id)).WillRepeatedly(ReturnRef(opponent));
        EXPECT_CALL(repositoryMock, GetOpponent(player.Id)).WillRepeatedly(ReturnRef(opponent));
        EXPECT_CALL(repositoryMock, GetOpponent(opponent.Id)).WillRepeatedly(ReturnRef(player));
        EXPECT_CALL(repositoryMock, GetPlayers).WillRepeatedly(Return(players));

        //setup random mock
        EXPECT_CALL(randomProviderMock, Next).WillRepeatedly(Return(1));
    }
};

TEST_F(GameEngineTestSuite, 1ShouldAddPlayerToRepoWhenConnected) {
    EXPECT_CALL(repositoryMock, AddPlayer(player.Id)).Times(Exactly(1));
    sut.PlayerConnected(player.Id);
}

TEST_F(GameEngineTestSuite, 2ShouldNotifyOpponentWhenPlayerLeftGivenTwoPlayers) {
    EXPECT_CALL(repositoryMock, GetPlayerCount).WillOnce(Return(2));
    EXPECT_CALL(gameInterfaceMock, NotifyGameAbandoned(opponent.Id, player.PlayerName)).Times(Exactly(1));
    sut.PlayerLeft(player.Id);
}

TEST_F(GameEngineTestSuite, 3ShouldNotNotifyOpponentWhenPlayerLeftGivenOnePlayer) {
    EXPECT_CALL(repositoryMock, GetPlayerCount).WillOnce(Return(1));
    EXPECT_CALL(gameInterfaceMock, NotifyGameAbandoned(opponent.Id, player.PlayerName)).Times(Exactly(0));
    sut.PlayerLeft(player.Id);
}

TEST_F(GameEngineTestSuite, 4ShouldLoginAndAskToWaitPlayerUponFirstInputGivenOnePlayer) {
    const string LOGIN_NAME = "pLaYeROnE";
    player.PlayerName = "";
    string actualName;

    EXPECT_CALL(repositoryMock, GetPlayerCount).WillOnce(Return(1));
    EXPECT_CALL(repositoryMock, SetPlayerName).WillOnce(SaveArg<1>(&actualName));
    EXPECT_CALL(gameInterfaceMock, NotifyWaitForOpponent(player.Id)).Times(Exactly(1));
    sut.PlayerInput(player.Id, LOGIN_NAME);

    ASSERT_EQ(LOGIN_NAME, actualName);
}

TEST_F(GameEngineTestSuite, 5ShouldLoginAndNotifyFirstPlayerGivenSecondPlayerConnected) {
    const string LOGIN_NAME = "pLaYeRTwo";
    opponent.PlayerName = "";
    string actualName;

    EXPECT_CALL(repositoryMock, SetPlayerName(opponent.Id, _)).WillOnce(SaveArg<1>(&actualName));
    EXPECT_CALL(repositoryMock, GetPlayerCount).WillOnce(Return(2));
    EXPECT_CALL(gameInterfaceMock, NotifyOpponentConnected(player.Id, LOGIN_NAME)).Times(Exactly(1));
    sut.PlayerInput(opponent.Id, LOGIN_NAME);

    ASSERT_EQ(LOGIN_NAME, actualName);
}

TEST_F(GameEngineTestSuite, 6ShouldStartNewGameGivenSecondPlayerConnected) {
    opponent.PlayerName = "";

    EXPECT_CALL(repositoryMock, GetPlayerCount).WillOnce(Return(2));
    EXPECT_CALL(gameInterfaceMock, NotifyGameStarting).Times(Exactly(1));
    sut.PlayerInput(opponent.Id, opponent.PlayerName);
}

TEST_F(GameEngineTestSuite, 7ShouldIgnoreUnexpectedInputGivenNotEnoughPlayers) {
    EXPECT_CALL(repositoryMock, GetPlayerCount).WillRepeatedly(Return(1));
    EXPECT_CALL(repositoryMock, AddPlayerTurn).Times(Exactly(0));
    sut.PlayerInput(opponent.Id, "iddqd");
}

TEST_F(GameEngineTestSuite, 8ShouldIgnoreOutOfTurnInput) {
    EXPECT_CALL(repositoryMock, GetPlayerCount).WillRepeatedly(Return(2));
    EXPECT_CALL(repositoryMock, GetActingPlayerId).WillOnce(Return(player.Id));
    EXPECT_CALL(repositoryMock, AddPlayerTurn).Times(Exactly(0));
    sut.PlayerInput(opponent.Id, "2");
}

TEST_F(GameEngineTestSuite, 9ShouldNotifyInvalidInputGivenNotDigit) {
    EXPECT_CALL(repositoryMock, GetPlayerCount).WillRepeatedly(Return(2));
    EXPECT_CALL(repositoryMock, GetActingPlayerId).WillOnce(Return(opponent.Id));
    EXPECT_CALL(gameInterfaceMock, RetryInvalidInput(opponent.Id)).Times(Exactly(1));
    EXPECT_CALL(repositoryMock, AddPlayerTurn).Times(Exactly(0));
    sut.PlayerInput(opponent.Id, "idkfa");
}

TEST_F(GameEngineTestSuite, 10ShouldNotifyInvalidInputGivenOutOfBoundsLow) {
    EXPECT_CALL(repositoryMock, GetPlayerCount).WillRepeatedly(Return(2));
    EXPECT_CALL(repositoryMock, GetActingPlayerId).WillOnce(Return(opponent.Id));
    EXPECT_CALL(gameInterfaceMock, RetryInvalidInput(opponent.Id)).Times(Exactly(1));
    EXPECT_CALL(repositoryMock, AddPlayerTurn).Times(Exactly(0));
    sut.PlayerInput(opponent.Id, "0");
}

TEST_F(GameEngineTestSuite, 11ShouldNotifyInvalidInputGivenOutOfBoundsHigh) {
    EXPECT_CALL(repositoryMock, GetPlayerCount).WillRepeatedly(Return(2));
    EXPECT_CALL(repositoryMock, GetActingPlayerId).WillOnce(Return(opponent.Id));
    EXPECT_CALL(gameInterfaceMock, RetryInvalidInput(opponent.Id)).Times(Exactly(1));
    EXPECT_CALL(repositoryMock, AddPlayerTurn).Times(Exactly(0));
    sut.PlayerInput(opponent.Id, "10");
}

TEST_F(GameEngineTestSuite, 12ShouldProcessPlayerTurn) {
    EXPECT_CALL(repositoryMock, GetPlayerCount).WillRepeatedly(Return(2));
    EXPECT_CALL(repositoryMock, GetActingPlayerId).WillOnce(Return(player.Id));
    EXPECT_CALL(repositoryMock, AddPlayerTurn(player.Id, 1)).Times(Exactly(1));
    EXPECT_CALL(winningConditionsMock, IsGameWon).Times(Exactly(1));
    EXPECT_CALL(repositoryMock, SetActingPlayerId(opponent.Id)).Times(Exactly(1));
    sut.PlayerInput(player.Id, "1");
}

TEST_F(GameEngineTestSuite, 13ShouldShuffleStartingPlayerRandomly) {
    opponent.PlayerName = "";
    EXPECT_CALL(randomProviderMock, Next).WillRepeatedly(Return(0));
    EXPECT_CALL(repositoryMock, GetPlayerCount).WillRepeatedly(Return(2));
    EXPECT_CALL(repositoryMock, SetActingPlayerId(player.Id)).Times(Exactly(1));
    sut.PlayerInput(opponent.Id, opponent.PlayerName);
}

TEST_F(GameEngineTestSuite, 14ShouldShuffleStartingPlayerRandomly) {
    opponent.PlayerName = "";
    EXPECT_CALL(randomProviderMock, Next).WillRepeatedly(Return(1));
    EXPECT_CALL(repositoryMock, GetPlayerCount).WillRepeatedly(Return(2));
    EXPECT_CALL(repositoryMock, SetActingPlayerId(opponent.Id)).Times(Exactly(1));
    sut.PlayerInput(opponent.Id, opponent.PlayerName);
}
