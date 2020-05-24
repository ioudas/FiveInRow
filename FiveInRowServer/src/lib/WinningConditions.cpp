#include <Exceptions/ServerException.h>
#include "WinningConditions.h"

bool WinningConditions::IsGameWon(GameState gameState, Coords from) const {

    auto symbol = gameState.Board[from.x][from.y];

    if (symbol == '\0')
        return false;

    return Traverse(gameState.Board, from, Direction::Any, symbol, 1);
}

bool WinningConditions::Traverse(vector<vector<char>> board, Coords coords, Direction directionRestriction,
                                 char symbol, int victoryPoints) const {
    std::printf("Moving %d from x:%d y:%d\n", directionRestriction, coords.x, coords.y);
    std::printf("Victory points: %d\n", victoryPoints);
    if (symbol != board[coords.x][coords.y]) {
        std::printf("Check failed\n");
        return false;
    }

    if (victoryPoints++ == 5) {
        std::printf("WIN\n");
        return true;
    }

    if (directionRestriction != Direction::Any)
        return CanMove(coords, directionRestriction) &&
               Traverse(board, GetCoords(coords, directionRestriction), directionRestriction, symbol, victoryPoints);

    for (int dir = Direction::Left; dir <= Direction::Down; dir++) {
        auto isPathToVictory = CanMove(coords, Direction(dir)) &&
                               Traverse(board, GetCoords(coords, Direction(dir)), Direction(dir), symbol,
                                        victoryPoints);
        if (isPathToVictory) {
            std::printf("Path clear\n");
            return true;
        }
    }

    std::printf("Path failed\n");

    return false;
}

Coords WinningConditions::GetCoords(Coords coords, Direction direction) const {
    switch (direction) {
        case Direction::Left:
            return Coords(coords.x - 1, coords.y);
        case Direction::LeftUp:
            return Coords(coords.x - 1, coords.y + 1);
        case Direction::LeftDown:
            return Coords(coords.x - 1, coords.y - 1);
        case Direction::Right:
            return Coords(coords.x + 1, coords.y);
        case Direction::RightUp:
            return Coords(coords.x + 1, coords.y + 1);
        case Direction::RightDown:
            return Coords(coords.x + 1, coords.y - 1);
        case Direction::Up:
            return Coords(coords.x, coords.y + 1);
        case Direction::Down:
            return Coords(coords.x, coords.y - 1);
        default:
            throw new ServerException("Invalid direction " + std::to_string(direction));
    }
}

bool WinningConditions::CanMove(Coords from, Direction direction) const {
    switch (direction) {
        case Direction::Left:
            return from.x > 0;
        case Direction::LeftUp:
            return CanMove(from, Direction::Left) && CanMove(from, Direction::Up);
        case Direction::LeftDown:
            return CanMove(from, Direction::Left) && CanMove(from, Direction::Down);
        case Direction::Right:
            return from.x < 8;
        case Direction::RightUp:
            return CanMove(from, Direction::Right) && CanMove(from, Direction::Up);
        case Direction::RightDown:
            return CanMove(from, Direction::Right) && CanMove(from, Direction::Down);
        case Direction::Up:
            return from.y < 5;
        case Direction::Down:
            return from.y > 0;
        default:
            throw new ServerException("Invalid direction " + std::to_string(direction));
    }
}
