#include "gtest/gtest.h"
#include "WinningConditions.h"

TEST(WinningConditionsTestSuite, ShouldReturnFalseGivenEmptyBoard) {
    WinningConditions sut;
    auto expectedResult = false;
    GameState gameState;

    auto actualResult = sut.IsGameWon(gameState);

    ASSERT_EQ(expectedResult, actualResult);
}

TEST(WinningConditionsTestSuite, ShouldReturnWinnerGivenHorizontalWin) {
    auto expectedResult = true;
    WinningConditions sut;
    GameState gameState;
    gameState.Board[1][3] = 'x';
    gameState.Board[2][3] = 'x';
    gameState.Board[3][3] = 'x';
    gameState.Board[4][3] = 'x';
    gameState.Board[5][3] = 'x';

    char winnerPlayerSymbol;
    auto actualResult = sut.IsGameWon(gameState, winnerPlayerSymbol);

    ASSERT_EQ(expectedResult, actualResult);
    ASSERT_EQ('x', winnerPlayerSymbol);
}

TEST(WinningConditionsTestSuite, ShouldReturnWinnerGivenVerticalWin) {
    auto expectedResult = true;
    WinningConditions sut;
    GameState gameState;
    gameState.Board[1][1] = 'x';
    gameState.Board[1][2] = 'x';
    gameState.Board[1][3] = 'x';
    gameState.Board[1][4] = 'x';
    gameState.Board[1][5] = 'x';

    char winnerPlayerSymbol;
    auto actualResult = sut.IsGameWon(gameState, winnerPlayerSymbol);

    ASSERT_EQ(expectedResult, actualResult);
    ASSERT_EQ('x', winnerPlayerSymbol);
}

TEST(WinningConditionsTestSuite, ShouldReturnWinnerGivenDiagonalWin) {
    auto expectedResult = true;
    WinningConditions sut;
    GameState gameState;
    gameState.Board[1][1] = 'x';
    gameState.Board[2][2] = 'x';
    gameState.Board[3][3] = 'x';
    gameState.Board[4][4] = 'x';
    gameState.Board[5][5] = 'x';

    char winnerPlayerSymbol;
    auto actualResult = sut.IsGameWon(gameState, winnerPlayerSymbol);

    ASSERT_EQ(expectedResult, actualResult);
    ASSERT_EQ('x', winnerPlayerSymbol);
}

TEST(WinningConditionsTestSuite, ShouldNotReturnWinnerGivenHorizontalGap) {
    auto expectedResult = false;
    WinningConditions sut;
    GameState gameState;
    gameState.Board[1][3] = 'x';
    gameState.Board[2][3] = 'x';
    gameState.Board[3][3] = '\0';
    gameState.Board[4][3] = 'x';
    gameState.Board[5][3] = 'x';

    char winnerPlayerSymbol;
    auto actualResult = sut.IsGameWon(gameState, winnerPlayerSymbol);

    ASSERT_EQ(expectedResult, actualResult);
}

TEST(WinningConditionsTestSuite, ShouldNotReturnWinnerGivenHorizontalInterruptedByOpponent) {
    auto expectedResult = false;
    WinningConditions sut;
    GameState gameState;
    gameState.Board[1][3] = 'x';
    gameState.Board[2][3] = 'x';
    gameState.Board[3][3] = 'o';
    gameState.Board[4][3] = 'x';
    gameState.Board[5][3] = 'x';

    char winnerPlayerSymbol;
    auto actualResult = sut.IsGameWon(gameState, winnerPlayerSymbol);

    ASSERT_EQ(expectedResult, actualResult);
}

TEST(WinningConditionsTestSuite, ShouldNotReturnWinnerGivenVerticalGap) {
    auto expectedResult = false;
    WinningConditions sut;
    GameState gameState;
    gameState.Board[1][1] = 'x';
    gameState.Board[2][2] = 'x';
    gameState.Board[3][3] = 'x';
    gameState.Board[4][4] = '\0';
    gameState.Board[5][5] = 'x';

    char winnerPlayerSymbol;
    auto actualResult = sut.IsGameWon(gameState, winnerPlayerSymbol);

    ASSERT_EQ(expectedResult, actualResult);
}

TEST(WinningConditionsTestSuite, ShouldNotReturnWinnerGivenVerticalInterruptedByOpponent) {
    auto expectedResult = false;
    WinningConditions sut;
    GameState gameState;
    gameState.Board[1][1] = 'x';
    gameState.Board[2][2] = 'x';
    gameState.Board[3][3] = 'x';
    gameState.Board[4][4] = 'o';
    gameState.Board[5][5] = 'x';

    char winnerPlayerSymbol;
    auto actualResult = sut.IsGameWon(gameState, winnerPlayerSymbol);

    ASSERT_EQ(expectedResult, actualResult);
}

TEST(WinningConditionsTestSuite, ShouldNotReturnWinnerGivenDiagonalGap) {
    auto expectedResult = false;
    WinningConditions sut;
    GameState gameState;
    gameState.Board[1][1] = 'x';
    gameState.Board[1][2] = 'x';
    gameState.Board[1][3] = 'x';
    gameState.Board[1][4] = '\0';
    gameState.Board[1][5] = 'x';

    char winnerPlayerSymbol;
    auto actualResult = sut.IsGameWon(gameState, winnerPlayerSymbol);

    ASSERT_EQ(expectedResult, actualResult);
}

TEST(WinningConditionsTestSuite, ShouldNotReturnWinnerGivenDiagonalInterruptedByOpponent) {
    auto expectedResult = false;
    WinningConditions sut;
    GameState gameState;
    gameState.Board[1][1] = 'x';
    gameState.Board[1][2] = 'x';
    gameState.Board[1][3] = 'x';
    gameState.Board[1][4] = 'o';
    gameState.Board[1][5] = 'x';

    char winnerPlayerSymbol;
    auto actualResult = sut.IsGameWon(gameState, winnerPlayerSymbol);

    ASSERT_EQ(expectedResult, actualResult);
}
