project(FiveInRowServerLib)

set(HEADER_FILES
        GameEngine.h
        GameInterface.h
        Repository.h
        Server.h
        WinningConditions.h
        BoardFormatter.h
        ProtocolHelper.h
        Util/RandomProvider.h
        )

set(SOURCE_FILES
        GameEngine.cpp
        GameInterface.cpp
        Repository.cpp
        Server.cpp
        WinningConditions.cpp
        BoardFormatter.cpp
        ProtocolHelper.cpp
        Exceptions/ServerException.h
        Models/GameState.h
        Models/MessageType.h
        Models/Player.h
        Models/Coords.h
        Util/StringUtil.cpp
        Util/RandomProvider.cpp)

add_library(FiveInRowServerLib STATIC ${SOURCE_FILES} ${HEADER_FILES})