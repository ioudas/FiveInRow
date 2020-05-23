#include "gmock/gmock.h"
#include "GameInterface.h"

class GameInterfaceMock : public IGameInterface {
public:
    MOCK_METHOD(void, NotifyWelcome, (int playerId, string playerName), (override));
    MOCK_METHOD(void, NotifyWaitForOpponent, (int playerId), (override));
    MOCK_METHOD(void, NotifyOpponentConnected, (int playerId, string opponentName), (override));
    MOCK_METHOD(void, NotifyGameStarting, (), (override));
    MOCK_METHOD(void, SendBoardState, (), (override));
    MOCK_METHOD(void, NotifyWaitForOpponentTurn, (int playerId, string opponentName), (override));
    MOCK_METHOD(void, NotifyPlayerTurn, (int playerId), (override));
    MOCK_METHOD(void, RetryInvalidInput, (int playerId), (override));
    MOCK_METHOD(void, NotifyGameWon, (string winnerPlayerName), (override));
    MOCK_METHOD(void, NotifyGameAbandoned, (int winnerPlayerId, string playerLeftName), (override));
};