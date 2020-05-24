#include "gtest/gtest.h"
#include "WinningConditions.h"

class WinningConditionsTestSuite : public ::testing::Test {
protected:
    WinningConditions sut;
    GameState GetHorizontalWinBoard() {
        GameState gameState;
        gameState.Board[1][3] = 'x';
        gameState.Board[2][3] = 'x';
        gameState.Board[3][3] = 'x';
        gameState.Board[4][3] = 'x';
        gameState.Board[5][3] = 'x';

        return gameState;
    }

    GameState GetVerticalWinBoard() {
        GameState gameState;
        gameState.Board[1][1] = 'x';
        gameState.Board[1][2] = 'x';
        gameState.Board[1][3] = 'x';
        gameState.Board[1][4] = 'x';
        gameState.Board[1][5] = 'x';

        return gameState;
    }

    GameState GetDiagonalWinBoard() {
        GameState gameState;
        gameState.Board[1][1] = 'x';
        gameState.Board[2][2] = 'x';
        gameState.Board[3][3] = 'x';
        gameState.Board[4][4] = 'x';
        gameState.Board[5][5] = 'x';

        return gameState;
    }
};

TEST_F(WinningConditionsTestSuite, ShouldReturnFalseGivenEmptyBoard) {
    GameState gameState;

    auto actualResult = sut.IsGameWon(gameState, Coords(0, 0));

    ASSERT_EQ(false, actualResult);
}

TEST_F(WinningConditionsTestSuite, ShouldReturnTrueGivenHorizontalWinFromStart) {
    auto gameState = GetHorizontalWinBoard();

    auto actualResult = sut.IsGameWon(gameState, Coords(1, 3));

    ASSERT_EQ(true, actualResult);
}

TEST_F(WinningConditionsTestSuite, ShouldReturnFalseGivenHorizontalOneShort) {
    auto gameState = GetHorizontalWinBoard();
    gameState.Board[5][3] = '\0';

    auto actualResult = sut.IsGameWon(gameState, Coords(4, 3));

    ASSERT_EQ(false, actualResult);
}

TEST_F(WinningConditionsTestSuite, ShouldReturnTrueGivenHorizontalWinFromEnd) {
    auto gameState = GetHorizontalWinBoard();

    auto actualResult = sut.IsGameWon(gameState, Coords(5, 3));

    ASSERT_EQ(true, actualResult);
}

TEST_F(WinningConditionsTestSuite, ShouldReturnTrueGivenVerticalWin) {
    auto gameState = GetVerticalWinBoard();

    auto actualResult = sut.IsGameWon(gameState, Coords(1, 1));

    ASSERT_EQ(true, actualResult);
}

TEST_F(WinningConditionsTestSuite, ShouldReturnFalseGivenVerticalOneShort) {
    auto gameState = GetVerticalWinBoard();
    gameState.Board[1][5] = '\0';

    auto actualResult = sut.IsGameWon(gameState, Coords(1, 4));

    ASSERT_EQ(false, actualResult);
}

TEST_F(WinningConditionsTestSuite, ShouldReturnTrueGivenDiagonalWin) {
    auto gameState = GetDiagonalWinBoard();

    auto actualResult = sut.IsGameWon(gameState, Coords(1, 1));

    ASSERT_EQ(true, actualResult);
}

TEST_F(WinningConditionsTestSuite, ShouldReturnFalseGivenDiagonalOneShort) {
    auto gameState = GetDiagonalWinBoard();
    gameState.Board[5][5] = '\0';

    auto actualResult = sut.IsGameWon(gameState, Coords(4, 4));

    ASSERT_EQ(false, actualResult);
}

TEST_F(WinningConditionsTestSuite, ShouldReturnFalseGivenHorizontalGap) {
    auto gameState = GetHorizontalWinBoard();
    gameState.Board[3][3] = '\0';

    auto actualResult = sut.IsGameWon(gameState, Coords(1, 3));

    ASSERT_EQ(false, actualResult);
}

TEST_F(WinningConditionsTestSuite, ShouldReturnFalseGivenHorizontalInterruptedByOpponent) {
    auto gameState = GetHorizontalWinBoard();
    gameState.Board[3][3] = 'o';

    auto actualResult = sut.IsGameWon(gameState, Coords(1, 3));

    ASSERT_EQ(false, actualResult);
}

TEST_F(WinningConditionsTestSuite, ShouldReturnFalseGivenVerticalGap) {
    auto gameState = GetVerticalWinBoard();
    gameState.Board[1][4] = '\0';

    auto actualResult = sut.IsGameWon(gameState, Coords(1, 1));

    ASSERT_EQ(false, actualResult);
}

TEST_F(WinningConditionsTestSuite, ShouldReturnFalseGivenVerticalInterruptedByOpponent) {
    auto gameState = GetVerticalWinBoard();
    gameState.Board[1][4] = 'o';

    auto actualResult = sut.IsGameWon(gameState, Coords(1, 1));

    ASSERT_EQ(false, actualResult);
}

TEST_F(WinningConditionsTestSuite, ShouldReturnFalseGivenDiagonalGap) {
    auto gameState = GetDiagonalWinBoard();
    gameState.Board[4][4] = '\0';

    auto actualResult = sut.IsGameWon(gameState, Coords(1, 1));

    ASSERT_EQ(false, actualResult);
}

TEST_F(WinningConditionsTestSuite, ShouldReturnFalseGivenDiagonalInterruptedByOpponent) {
    auto gameState = GetDiagonalWinBoard();
    gameState.Board[4][4] = 'o';

    auto actualResult = sut.IsGameWon(gameState, Coords(1, 1));

    ASSERT_EQ(false, actualResult);
}
