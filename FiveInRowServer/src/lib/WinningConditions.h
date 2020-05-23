
#ifndef FIVEINROWSERVER_WINNINGCONDITIONS_H
#define FIVEINROWSERVER_WINNINGCONDITIONS_H

#include "Models/GameState.cpp"

class IWinningConditions {
public:
    virtual bool IsGameWon(GameState gameState, char &winnerPlayerSymbol) const = 0;
};

class WinningConditions : IWinningConditions{
public:
    bool IsGameWon(GameState gameState, char &winnerPlayerSymbol) const override;
};


#endif //FIVEINROWSERVER_WINNINGCONDITIONS_H
