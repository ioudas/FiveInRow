#ifndef FIVEINROWSERVER_BOARDFORMATTER_H
#define FIVEINROWSERVER_BOARDFORMATTER_H


#include <string>
#include "Models/GameState.cpp"
#include "Util/StringUtil.cpp"

class BoardFormatter {
public:
    static std::string GetAscii(GameState gameState);

    std::string GetLegend(GameState gameState);
};


#endif //FIVEINROWSERVER_BOARDFORMATTER_H
