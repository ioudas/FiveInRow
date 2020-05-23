project(FiveInRowServerLib)

set(HEADER_FILES
        GameEngine.h
        GameInterface.h
        Repository.h
        Server.h
        WinningConditions.h
        BoardFormatter.h
        ProtocolHelper.h
        )

set(SOURCE_FILES
        GameEngine.cpp
        GameInterface.cpp
        Repository.cpp
        Server.cpp
        WinningConditions.cpp
        BoardFormatter.cpp
        ProtocolHelper.cpp
        Exceptions/ServerException.cpp
        Models/GameState.cpp
        Models/MessageType.cpp
        Models/Player.cpp
        Util/StringUtil.cpp
        )

add_library(FiveInRowServerLib STATIC ${SOURCE_FILES} ${HEADER_FILES})