#ifndef FIVEINROWSERVER_PROTOCOLHELPER_H
#define FIVEINROWSERVER_PROTOCOLHELPER_H

#include "Models/MessageType.h"
#include <string>

class ProtocolHelper {
public:
    static const char * Serialize(MessageType messageType, std::string& message);
};


#endif //FIVEINROWSERVER_PROTOCOLHELPER_H
