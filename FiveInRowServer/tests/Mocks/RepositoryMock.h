#include "gmock/gmock.h"
#include "Repository.h"

class RepositoryMock : public IRepository {
public:
    MOCK_METHOD(GameState, GetGameState, (), (const, override));
    MOCK_METHOD(void, SetActingPlayerId, (int playerId), (override));
    MOCK_METHOD(int, GetActingPlayerId, (), (override));
    MOCK_METHOD(void, AddPlayerTurn, (int playerId, int columnNum), (override));
    MOCK_METHOD(void, AddPlayer, (int playerId), (override));
    MOCK_METHOD(void, SetPlayerName, (int playerId, std::string playerName), (override));
    MOCK_METHOD(int, GetPlayerCount, (), (override));
    MOCK_METHOD(Player&, GetPlayer, (int playerId), (override));
    MOCK_METHOD(std::vector<Player>,  GetPlayers, (), (override));
    MOCK_METHOD(Player&, GetOpponent, (int playerId), (override));
    MOCK_METHOD(char, GetPlayerSymbol, (int playerId), (override));
    MOCK_METHOD(void, ClearState, (), (override));
};