#include "app_exceptions.h"

#include <iostream>


ApplicationException::ApplicationException() :
    m_message { "[ApplicationException] " } {}

ApplicationException::ApplicationException(const std::string& message) :
    ApplicationException {} {
    m_message += message;
}

ApplicationException::ApplicationException(const char* message) :
    ApplicationException { std::string { message } } {}

const char* ApplicationException::what() const noexcept {
    return m_message.c_str();
}


EverywhereException::EverywhereException() :
    ApplicationException {} {
    m_message = "[EverywhereException] ";
}

EverywhereException::EverywhereException(const std::string& message) :
    EverywhereException {} {
    m_message += message;
}

EverywhereException::EverywhereException(const char* message) :
    EverywhereException { std::string { message } } {}


WindowException::WindowException() :
    ApplicationException {} {
    m_message = "[WindowException] ";
}

WindowException::WindowException(const std::string& message) :
    WindowException {} {
    m_message += message;
}

WindowException::WindowException(const char* message) :
    WindowException { std::string { message } } {}


OpenGLException::OpenGLException() :
    ApplicationException {} {
    m_message = "[OpenGLException] ";
}

OpenGLException::OpenGLException(const std::string& message) :
    OpenGLException {} {
    m_message += message;
}

OpenGLException::OpenGLException(const char* message) :
    OpenGLException { std::string { message } } {}


InputException::InputException() :
    ApplicationException {} {
    m_message = "[InputException] ";
}

InputException::InputException(const std::string& message) :
    InputException {} {
    m_message += message;
}

InputException::InputException(const char* message) :
    InputException { std::string { message } } {}


SpaceException::SpaceException() :
    ApplicationException {} {
    m_message = "[SpaceException] ";
}

SpaceException::SpaceException(const std::string& message) :
    SpaceException {} {
    m_message += message;
}

SpaceException::SpaceException(const char* message) :
    SpaceException { std::string { message } } {}


SceneException::SceneException() :
    ApplicationException {} {
    m_message = "[SceneException] ";
}

SceneException::SceneException(const std::string& message) :
    SceneException {} {
    m_message += message;
}

SceneException::SceneException(const char* message) :
    SceneException { std::string { message } } {}


ObjectException::ObjectException() :
    ApplicationException {} {
    m_message = "[ObjectException] ";
}

ObjectException::ObjectException(const std::string& message) :
    ObjectException {} {
    m_message += message;
}

ObjectException::ObjectException(const char* message) :
    ObjectException { std::string { message } } {}


MeshException::MeshException() :
    ApplicationException {} {
    m_message = "[MeshException] ";
}

MeshException::MeshException(const std::string& message) :
    MeshException {} {
    m_message += message;
}

MeshException::MeshException(const char* message) :
    MeshException { std::string { message } } {}


MaterialStorageException::MaterialStorageException() :
    ApplicationException {} {
    m_message = "[MaterialStorageException] ";
}

MaterialStorageException::MaterialStorageException(const std::string& message) :
    MaterialStorageException {} {
    m_message += message;
}

MaterialStorageException::MaterialStorageException(const char* message) :
    MaterialStorageException { std::string { message } } {}


MaterialException::MaterialException() :
    ApplicationException {} {
    m_message = "[MaterialException] ";
}

MaterialException::MaterialException(const std::string& message) :
    MaterialException {} {
    m_message += message;
}

MaterialException::MaterialException(const char* message) :
    MaterialException { std::string { message } } {}


ShaderException::ShaderException() :
    ApplicationException {} {
    m_message = "[ShaderException] ";
}

ShaderException::ShaderException(const std::string& message) :
    ShaderException {} {
    m_message += message;
}

ShaderException::ShaderException(const char* message) :
    ShaderException { std::string { message } } {}


VertexShaderException::VertexShaderException() :
    ShaderException {} {
    m_message = "[VertexShaderException] ";
}

VertexShaderException::VertexShaderException(const std::string& message) :
    VertexShaderException {} {
    m_message += message;
}

VertexShaderException::VertexShaderException(const char* message) :
    VertexShaderException { std::string { message } } {}


FragmentShaderException::FragmentShaderException() :
    ShaderException {} {
    m_message = "[FragmentShaderException] ";
}

FragmentShaderException::FragmentShaderException(const std::string& message) :
    FragmentShaderException {} {
    m_message += message;
}

FragmentShaderException::FragmentShaderException(const char* message) :
    FragmentShaderException { std::string { message } } {}


ProgramShaderException::ProgramShaderException() :
    ShaderException {} {
    m_message = "[ProgramShaderException] ";
}

ProgramShaderException::ProgramShaderException(const std::string& message) :
    ProgramShaderException {} {
    m_message += message;
}

ProgramShaderException::ProgramShaderException(const char* message) :
    ProgramShaderException { std::string { message } } {}


UniformShaderException::UniformShaderException() :
    ShaderException {} {
    m_message = "[UniformShaderException] ";
}

UniformShaderException::UniformShaderException(const std::string& message) :
    UniformShaderException {} {
    m_message += message;
}

UniformShaderException::UniformShaderException(const char* message) :
    UniformShaderException { std::string { message } } {}


TextureException::TextureException() :
    ApplicationException {} {
    m_message = "[TextureException] ";
}

TextureException::TextureException(const std::string& message) :
    TextureException {} {
    m_message += message;
}

TextureException::TextureException(const char* message) :
    TextureException { std::string { message } } {}


ModelException::ModelException() :
    ApplicationException {} {
    m_message = "[ModelException] ";
}

ModelException::ModelException(const std::string& message) :
    ModelException {} {
    m_message += message;
}

ModelException::ModelException(const char* message) :
    ModelException { std::string { message } } {}


ModelStorageException::ModelStorageException() :
    ApplicationException {} {
    m_message = "[ModelStorageException] ";
}

ModelStorageException::ModelStorageException(const std::string& message) :
    ModelStorageException {} {
    m_message += message;
}

ModelStorageException::ModelStorageException(const char* message) :
    ModelStorageException { std::string { message } } {}


ModelDataException::ModelDataException() :
    ApplicationException {} {
    m_message = "[ModelDataException] ";
}

ModelDataException::ModelDataException(const std::string& message) :
    ModelDataException {} {
    m_message += message;
}

ModelDataException::ModelDataException(const char* message) :
    ModelDataException { std::string { message } } {}


ModelDataImporterException::ModelDataImporterException() :
    ApplicationException {} {
    m_message = "[ModelDataImporterException] ";
}

ModelDataImporterException::ModelDataImporterException(const std::string& message) :
    ModelDataImporterException {} {
    m_message += message;
}

ModelDataImporterException::ModelDataImporterException(const char* message) :
    ModelDataImporterException { std::string { message } } {}


FilesystemException::FilesystemException() :
    ApplicationException {} {
    m_message = "[FilesystemException] ";
}

FilesystemException::FilesystemException(const std::string& message) :
    FilesystemException {} {
    m_message += message;
}

FilesystemException::FilesystemException(const char* message) :
    FilesystemException { std::string { message } } {}
