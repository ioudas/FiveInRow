#ifndef FIVEINROWSERVER_GAMESTATE_C
#define FIVEINROWSERVER_GAMESTATE_C

#include <vector>
#include "Models/Player.h"

using std::vector;

class GameState {
public:
    vector<vector<char>> Board = vector(9, vector<char>(6)); //[column][row]
    std::vector<Player> Players;
    int ActingPlayerId;
};

#endif //FIVEINROWSERVER_GAMESTATE_C