
#ifndef FIVEINROWSERVER_COORDS_H
#define FIVEINROWSERVER_COORDS_H

struct Coords {
    int x;
    int y;

    Coords(int x, int y) : x(x), y(y) {};
};

#include "Models/GameState.h"

#endif //FIVEINROWSERVER_COORDS_H
