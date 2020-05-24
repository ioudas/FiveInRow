#ifndef FIVEINROWSERVER_BOARDFORMATTER_H
#define FIVEINROWSERVER_BOARDFORMATTER_H


#include <string>
#include "Models/GameState.h"
#include "Util/StringUtil.cpp"

class IBoardFormatter {
public:
    virtual std::string GetAscii(GameState gameState) const = 0;
    virtual std::string GetLegend(GameState gameState) const = 0;
};

class BoardFormatter : IBoardFormatter {
public:
    std::string GetAscii(GameState gameState) const override;
    std::string GetLegend(GameState gameState) const override;
};


#endif //FIVEINROWSERVER_BOARDFORMATTER_H
