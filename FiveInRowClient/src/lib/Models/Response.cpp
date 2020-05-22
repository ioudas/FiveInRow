#ifndef FIVEINROWCLIENT_RESPONSE_C
#define FIVEINROWCLIENT_RESPONSE_C

#include <string>
#include "MessageType.cpp"

class Response {
public:
    MessageType Type;
    std::string Message;

    Response(MessageType messageType, std::string message) :
            Type(messageType),
            Message(message) {}


};

#endif //FIVEINROWCLIENT_RESPONSE_C