project(FiveInRowTests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR}
        ${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

add_executable(TestRun
        GameEngineTest.cpp
        BoardFormatterTest.cpp
        RepositoryTest.cpp
        WinningConditionsTest.cpp
        Mocks/ServerMock.h
        Mocks/GameInterfaceMock.h
        Mocks/BoardFormatterMock.h
        Mocks/WinningConditionsMock.h
        Mocks/RepositoryMock.h)

target_link_libraries(TestRun FiveInRowServerLib)

target_link_libraries(TestRun gtest gtest_main gmock)