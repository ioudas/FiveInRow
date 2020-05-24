
#ifndef FIVEINROWSERVER_SERVEREXCEPTION_H
#define FIVEINROWSERVER_SERVEREXCEPTION_H

#include <string>

class ServerException : public std::exception {
    const std::string Message;
public:


    ServerException(const std::string &message) : std::exception(),
                                                  Message(message)
    {
    }

    ~ServerException() override {

    }

    const char* what() const noexcept {
        return Message.c_str();
    }
};

#endif //FIVEINROWSERVER_SERVEREXCEPTION_H
