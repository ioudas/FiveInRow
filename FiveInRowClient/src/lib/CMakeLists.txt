project(FiveInRowClientLib)

set(HEADER_FILES
        Client.h
        Game.h
        ProtocolHelper.h
        Constants.h
        )

set(SOURCE_FILES
        Client.cpp
        Game.cpp
        ProtocolHelper.cpp
        Models/MessageType.cpp
        Models/Response.cpp
        Exceptions/ClientException.cpp
        )

add_library(FiveInRowClientLib STATIC ${SOURCE_FILES} ${HEADER_FILES})