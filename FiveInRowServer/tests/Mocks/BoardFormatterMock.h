#include "gmock/gmock.h"
#include "BoardFormatter.h"

class BoardFormatterMock : public IBoardFormatter {
public:
    MOCK_METHOD(std::string, GetAscii, (GameState gameState), (const, override));
    MOCK_METHOD(std::string, GetLegend, (GameState gameState), (const, override));
};