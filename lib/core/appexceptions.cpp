#include "appexceptions.h"


ApplicationException::ApplicationException() :
    m_message { "[ApplicationException] " } {}

ApplicationException::ApplicationException(const std::string& message) :
    ApplicationException {}
{
    m_message += message;
}

ApplicationException::ApplicationException(const char* message) :
    ApplicationException { std::string { message } } {}

const char* ApplicationException::what() const noexcept {
    return m_message.c_str();
}
