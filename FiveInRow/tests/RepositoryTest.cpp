#include "gtest/gtest.h"
#include "Repository.h"

TEST(RepositoryTestSuite, ShouldCorrectPlayerCount) {
    Repository sut;
    auto expectedResult = 2;
    sut.AddPlayer(16);
    sut.AddPlayer(32);

    auto actualResult = sut.GetPlayerCount();

    ASSERT_EQ(expectedResult, actualResult);
}

TEST(RepositoryTestSuite, ShouldEmptyPlayerCount) {
    Repository sut;
    auto expectedResult = 0;

    auto actualResult = sut.GetPlayerCount();

    ASSERT_EQ(expectedResult, actualResult);
}

TEST(RepositoryTestSuite, ShouldSetPlayerName) {
    Repository sut;
    auto expectedResult = "Player2";
    sut.AddPlayer(16);
    sut.SetPlayerName(16, expectedResult);

    auto actualResult = sut.GetPlayer(16).PlayerName;

    ASSERT_EQ(expectedResult, actualResult);
}

TEST(RepositoryTestSuite, ShouldSetActingPlayerId) {
    Repository sut;
    auto expectedResult = 16;
    sut.SetActingPlayerId(expectedResult);

    auto actualResult = sut.GetActingPlayerId();

    ASSERT_EQ(expectedResult, actualResult);
}

TEST(RepositoryTestSuite, ShouldClearState) {
    Repository sut;
    sut.AddPlayer(1);
    sut.SetPlayerName(1, "P1");
    sut.AddPlayer(2);
    sut.SetPlayerName(2, "P2");
    sut.AddPlayerTurn(1, 1);
    sut.AddPlayerTurn(2, 3);

    sut.ClearState();

    ASSERT_EQ(0, sut.GetPlayerCount());
    ASSERT_EQ('\0', sut.GetGameState().Board[0][0]);
    ASSERT_EQ('\0', sut.GetGameState().Board[2][0]);
}

TEST(RepositoryTestSuite, ShouldFindOpponent) {
    Repository sut;
    int expectedResult = 1;
    sut.AddPlayer(1);
    sut.SetPlayerName(1, "P1");
    sut.AddPlayer(2);
    sut.SetPlayerName(2, "P2");

    int actualResult = sut.GetOpponent(2).Id;

    ASSERT_EQ(expectedResult, actualResult);
}

TEST(RepositoryTestSuite, ShouldEmptyPlayerSetGivenNoPlayers) {
    Repository sut;

    int actualResult = sut.GetPlayers().size();

    ASSERT_EQ(0, actualResult);
}

TEST(RepositoryTestSuite, ShouldFailWhenSetNameGivenNoPlayers) {
    Repository sut;

    ASSERT_DEATH(sut.SetPlayerName(2, "P1"), "");
}

TEST(RepositoryTestSuite, ShouldFailWhenAddPlayerTurnGivenNoPlayers) {
    Repository sut;

    ASSERT_DEATH(sut.AddPlayerTurn(2, 1), "");
}