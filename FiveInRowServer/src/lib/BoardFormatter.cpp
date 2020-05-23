#include <algorithm>
#include "BoardFormatter.h"


std::string BoardFormatter::GetAscii(GameState gameState) const{
    std::string boardAscii;
    boardAscii.append("Board:\n");
    for (int rowIdx = 5; rowIdx >= 0; rowIdx--) {
        for (int columnIdx = 0; columnIdx < 9; columnIdx++) {

            vector<char> &vector1 = gameState.Board[columnIdx];
            char symbol = vector1[rowIdx];
            if (symbol == '\0') {
                symbol = ' ';
            }
            auto cell = string_format("[%c]", symbol);
            boardAscii.append(cell.c_str());
        }
        boardAscii.append("\n");
    }

    return boardAscii;
}

std::string BoardFormatter::GetLegend(GameState gameState) const{
    std::string legend;
    legend.append("Legend:\n");
    for (Player player : gameState.Players) {
        auto legendLine = string_format("[%c] = %s\n", player.Symbol, player.PlayerName.c_str());
        legend.append(legendLine);
    }

    return legend;
}


