
#ifndef FIVEINROWSERVER_WINNINGCONDITIONS_H
#define FIVEINROWSERVER_WINNINGCONDITIONS_H

#include "Models/GameState.h"
#include "Models/Coords.h"

enum Direction {
    Any = 0,
    Left,
    LeftUp,
    LeftDown,
    Up,
    Right,
    RightUp,
    RightDown,
    Down
};

class IWinningConditions {
public:
    virtual bool IsGameWon(GameState gameState, Coords from) const = 0;
};

class WinningConditions : public IWinningConditions {
public:
    bool IsGameWon(GameState gameState, Coords from) const override;
private:
    bool Traverse(vector<vector<char>> board, Coords coords, Direction directionRestriction, char symbol, int victoryPoints) const;
    bool CanMove(Coords from, Direction direction) const;
    Coords GetCoords(Coords coords, Direction direction) const;
};

#endif //FIVEINROWSERVER_WINNINGCONDITIONS_H
