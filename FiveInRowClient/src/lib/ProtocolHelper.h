#ifndef FIVEINROWCLIENT_PROTOCOLHELPER_H
#define FIVEINROWCLIENT_PROTOCOLHELPER_H

#include "Models/Response.cpp"
class ProtocolHelper {
public:
    static Response Deserialize(const char * buffer);
};


#endif //FIVEINROWCLIENT_PROTOCOLHELPER_H
