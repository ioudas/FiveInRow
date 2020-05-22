#include "gtest/gtest.h"
#include "BoardFormatter.h"

TEST(BoardFormatterTestSuite, ShouldPrintEmptyBoard){
    BoardFormatter sut;
    GameState gameState;

    auto actualResult = sut.GetAscii(gameState);
    auto expectedResult = "Board:\n"
                          "[ ][ ][ ][ ][ ][ ][ ][ ][ ]\n"
                          "[ ][ ][ ][ ][ ][ ][ ][ ][ ]\n"
                          "[ ][ ][ ][ ][ ][ ][ ][ ][ ]\n"
                          "[ ][ ][ ][ ][ ][ ][ ][ ][ ]\n"
                          "[ ][ ][ ][ ][ ][ ][ ][ ][ ]\n"
                          "[ ][ ][ ][ ][ ][ ][ ][ ][ ]\n";

    ASSERT_EQ(expectedResult, actualResult);
}

TEST(BoardFormatterTestSuite, ShouldPrintFullBoard){
    BoardFormatter sut;
    GameState gameState;
    for (int column = 0; column < 9; ++column) {
        for (int row = 0; row < 6; ++row) {
            gameState.Board[column][row] = 'x';
        }
    }
    auto expectedResult = "Board:\n"
                          "[x][x][x][x][x][x][x][x][x]\n"
                          "[x][x][x][x][x][x][x][x][x]\n"
                          "[x][x][x][x][x][x][x][x][x]\n"
                          "[x][x][x][x][x][x][x][x][x]\n"
                          "[x][x][x][x][x][x][x][x][x]\n"
                          "[x][x][x][x][x][x][x][x][x]\n";

    auto actualResult = sut.GetAscii(gameState);

    ASSERT_EQ(expectedResult, actualResult);
}

TEST(BoardFormatterTestSuite, ShouldPrintModelGame){

    BoardFormatter sut;
    GameState gameState;
    gameState.Board[1][0] = 'x';
    gameState.Board[2][0] = 'o';
    gameState.Board[2][1] = 'x';
    gameState.Board[3][0] = 'o';
    gameState.Board[3][1] = 'x';
    gameState.Board[3][2] = 'o';
    gameState.Board[4][0] = 'o';
    gameState.Board[5][0] = 'x';
    gameState.Board[5][1] = 'x';
    gameState.Board[5][2] = 'o';
    gameState.Board[6][0] = 'x';
    gameState.Board[7][0] = 'o';
    gameState.Board[7][1] = 'o';
    gameState.Board[8][0] = 'x';
    auto expectedResult = "Board:\n"
                          "[ ][ ][ ][ ][ ][ ][ ][ ][ ]\n"
                          "[ ][ ][ ][ ][ ][ ][ ][ ][ ]\n"
                          "[ ][ ][ ][ ][ ][ ][ ][ ][ ]\n"
                          "[ ][ ][ ][o][ ][o][ ][ ][ ]\n"
                          "[ ][ ][x][x][ ][x][ ][o][ ]\n"
                          "[ ][x][o][o][o][x][x][o][x]\n";

    auto actualResult = sut.GetAscii(gameState);

    ASSERT_EQ(expectedResult, actualResult);
}

TEST(BoardFormatterTestSuite, ShouldPrintLegend){
    BoardFormatter sut;
    GameState gameState;
    Player player1 = Player(0);
    player1.Symbol = 'x';
    player1.PlayerName = "Player1";
    Player player2 = Player(0);
    player2.Symbol = 'o';
    player2.PlayerName = "Player2";
    gameState.Players.emplace_back(player1);
    gameState.Players.emplace_back(player2);
    auto expectedResult = "Legend:\n"
                          "[x] = Player1\n"
                          "[o] = Player2\n";

    auto actualResult = sut.GetLegend(gameState);

    ASSERT_EQ(expectedResult, actualResult);
}

