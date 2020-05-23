
#ifndef FIVEINROWSERVER_WINNINGCONDITIONS_H
#define FIVEINROWSERVER_WINNINGCONDITIONS_H

#include "Models/GameState.cpp"

class WinningConditions {
public:
    bool IsGameWon(GameState gameState, char &winnerPlayerSymbol);
};


#endif //FIVEINROWSERVER_WINNINGCONDITIONS_H
