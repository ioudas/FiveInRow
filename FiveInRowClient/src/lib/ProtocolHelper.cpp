#include <cstring>
#include "ProtocolHelper.h"

Response ProtocolHelper::Deserialize(const char * const buffer) {
    //first bit is message type
    auto messageType = static_cast<MessageType>(buffer[0] - '0');

    //rest is payload
    const char * payload = buffer + 1;

    return Response(messageType, std::string(payload));
}
