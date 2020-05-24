
#include <cstdlib>
#include "RandomProvider.h"

int RandomProvider::Next(int minValue, int maxValue) const {
    return rand() % (maxValue - minValue + 1) + minValue;
}
