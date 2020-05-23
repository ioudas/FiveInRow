#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Mocks/ServerMock.h"
#include "Mocks/RepositoryMock.h"
#include "Mocks/BoardFormatterMock.h"
#include "Mocks/WinningConditionsMock.h"
#include "Mocks/GameInterfaceMock.h"
#include "GameEngine.h"

TEST(GameEngineTestSuite, ExampleTest){
    ServerMock serverMock;
    RepositoryMock repositoryMock;
    BoardFormatterMock boardFormatterMock;
    WinningConditionsMock winningConditionsMock;
    GameInterfaceMock gameInterfaceMock;

    GameEngine sut(repositoryMock, serverMock, gameInterfaceMock, winningConditionsMock);

}