#include <iostream>

class ClientException : public std::exception {
    const std::string Message;
public:


    ClientException(const std::string &message) : std::exception(),
                                                  Message(message)
    {
    }

    ~ClientException() override {

    }

    const char* what() const noexcept {
        return Message.c_str();
    }
};