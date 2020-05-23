#include "gmock/gmock.h"
#include "Server.h"

class RepositoryMock : IServer {
public:
    MOCK_METHOD(void, Start, (int), (override));
    MOCK_METHOD(void, SendMessageToPlayer, (MessageType messageType, int playerId, std::string message), (override));
    MOCK_METHOD(void, BroadCastMessage, (MessageType messageType, std::string message), (override));
    MOCK_METHOD(void, SetOnPlayerConnected, (std::function<void(int)> callback), (override));
    MOCK_METHOD(void, SetOnPlayerLeft, (std::function<void(int)> callback), (override));
    MOCK_METHOD(void, SetOnPlayerInput, (std::function<void(int, std::string)> callback), (override));
};