#include "gmock/gmock.h"
#include "Server.h"
class ServerMock: IServer {
public:
    MOCK_METHOD(void, Start, (int), (override));
};