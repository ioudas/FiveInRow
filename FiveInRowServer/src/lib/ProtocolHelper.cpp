#include "ProtocolHelper.h"

const char * ProtocolHelper::Serialize(MessageType messageType, std::string& message) {

    message.insert(0, std::to_string(messageType));

    return message.c_str();
}
