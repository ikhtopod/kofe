#include "app_exceptions.h"

#include <iostream>


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


WindowException::WindowException() : ApplicationException {} {
    m_message = "[WindowException] ";
}

WindowException::WindowException(const std::string& message) :
    WindowException {}
{
    m_message += message;
}

WindowException::WindowException(const char* message) :
    WindowException { std::string { message } } {}


OpenGLException::OpenGLException() : ApplicationException {} {
    m_message = "[OpenGLException] ";
}

OpenGLException::OpenGLException(const std::string& message) :
    OpenGLException {}
{
    m_message += message;
}

OpenGLException::OpenGLException(const char* message) :
    OpenGLException { std::string { message } } {}


InputException::InputException() : ApplicationException {} {
    m_message = "[InputException] ";
}

InputException::InputException(const std::string& message) :
    InputException {}
{
    m_message += message;
}

InputException::InputException(const char* message) :
    InputException { std::string { message } } {}


ShaderException::ShaderException() : ApplicationException {} {
    m_message = "[ShaderException] ";
}

ShaderException::ShaderException(const std::string& message) :
    ShaderException {}
{
    m_message += message;
}

ShaderException::ShaderException(const char* message) :
    ShaderException { std::string { message } } {}


TextureException::TextureException() : ApplicationException {} {
    m_message = "[TextureException] ";
}

TextureException::TextureException(const std::string& message) :
    TextureException {}
{
    m_message += message;
}

TextureException::TextureException(const char* message) :
    TextureException { std::string { message } } {}
