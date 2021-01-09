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


SpaceException::SpaceException() : ApplicationException {} {
    m_message = "[SpaceException] ";
}

SpaceException::SpaceException(const std::string& message) :
    SpaceException {}
{
    m_message += message;
}

SpaceException::SpaceException(const char* message) :
    SpaceException { std::string { message } } {}


SceneException::SceneException() : ApplicationException {} {
    m_message = "[SceneException] ";
}

SceneException::SceneException(const std::string& message) :
    SceneException {}
{
    m_message += message;
}

SceneException::SceneException(const char* message) :
    SceneException { std::string { message } } {}


ObjectException::ObjectException() : ApplicationException {} {
    m_message = "[ObjectException] ";
}

ObjectException::ObjectException(const std::string& message) :
    ObjectException {}
{
    m_message += message;
}

ObjectException::ObjectException(const char* message) :
    ObjectException { std::string { message } } {}


MeshException::MeshException() : ApplicationException {} {
    m_message = "[MeshException] ";
}

MeshException::MeshException(const std::string& message) :
    MeshException {}
{
    m_message += message;
}

MeshException::MeshException(const char* message) :
    MeshException { std::string { message } } {}


MaterialException::MaterialException() : ApplicationException {} {
    m_message = "[MaterialException] ";
}

MaterialException::MaterialException(const std::string& message) :
    MaterialException {}
{
    m_message += message;
}

MaterialException::MaterialException(const char* message) :
    MaterialException { std::string { message } } {}


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
