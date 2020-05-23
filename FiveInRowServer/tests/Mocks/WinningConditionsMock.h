#include "gmock/gmock.h"
#include "WinningConditions.h"

class WinningConditionsMock : public IWinningConditions {
public:
    MOCK_METHOD(bool, IsGameWon, (GameState gameState, char &winnerPlayerSymbol), (const, override));
};