#ifndef APP_EXCEPTIONS_H
#define APP_EXCEPTIONS_H

#include <exception>
#include <string>


class ApplicationException : public std::exception {
protected:
    std::string m_message;

protected:
    ApplicationException();

public:
    explicit ApplicationException(const std::string& message);
    explicit ApplicationException(const char* message);

    const char* what() const noexcept override;
};


class EverywhereException : public ApplicationException {
protected:
    EverywhereException();

public:
    explicit EverywhereException(const std::string& message);
    explicit EverywhereException(const char* message);
};


class WindowException : public ApplicationException {
protected:
    WindowException();

public:
    explicit WindowException(const std::string& message);
    explicit WindowException(const char* message);
};


class OpenGLException : public ApplicationException {
protected:
    OpenGLException();

public:
    explicit OpenGLException(const std::string& message);
    explicit OpenGLException(const char* message);
};


class InputException : public ApplicationException {
protected:
    InputException();

public:
    explicit InputException(const std::string& message);
    explicit InputException(const char* message);
};


class SpaceException : public ApplicationException {
protected:
    SpaceException();

public:
    explicit SpaceException(const std::string& message);
    explicit SpaceException(const char* message);
};


class SceneException : public ApplicationException {
protected:
    SceneException();

public:
    explicit SceneException(const std::string& message);
    explicit SceneException(const char* message);
};


class ObjectException : public ApplicationException {
protected:
    ObjectException();

public:
    explicit ObjectException(const std::string& message);
    explicit ObjectException(const char* message);
};


class MeshException : public ApplicationException {
protected:
    MeshException();

public:
    explicit MeshException(const std::string& message);
    explicit MeshException(const char* message);
};


class MaterialStorageException : public ApplicationException {
protected:
    MaterialStorageException();

public:
    explicit MaterialStorageException(const std::string& message);
    explicit MaterialStorageException(const char* message);
};


class MaterialException : public ApplicationException {
protected:
    MaterialException();

public:
    explicit MaterialException(const std::string& message);
    explicit MaterialException(const char* message);
};


class ShaderException : public ApplicationException {
protected:
    ShaderException();

public:
    explicit ShaderException(const std::string& message);
    explicit ShaderException(const char* message);
};


class VertexShaderException : public ShaderException {
protected:
    VertexShaderException();

public:
    explicit VertexShaderException(const std::string& message);
    explicit VertexShaderException(const char* message);
};


class FragmentShaderException : public ShaderException {
protected:
    FragmentShaderException();

public:
    explicit FragmentShaderException(const std::string& message);
    explicit FragmentShaderException(const char* message);
};


class ProgramShaderException : public ShaderException {
protected:
    ProgramShaderException();

public:
    explicit ProgramShaderException(const std::string& message);
    explicit ProgramShaderException(const char* message);
};


class UniformShaderException : public ShaderException {
protected:
    UniformShaderException();

public:
    explicit UniformShaderException(const std::string& message);
    explicit UniformShaderException(const char* message);
};


class TextureException : public ApplicationException {
protected:
    TextureException();

public:
    explicit TextureException(const std::string& message);
    explicit TextureException(const char* message);
};


class ModelStorageException : public ApplicationException {
protected:
    ModelStorageException();

public:
    explicit ModelStorageException(const std::string& message);
    explicit ModelStorageException(const char* message);
};


class ModelDataException : public ApplicationException {
protected:
    ModelDataException();

public:
    explicit ModelDataException(const std::string& message);
    explicit ModelDataException(const char* message);
};


class FilesystemException : public ApplicationException {
protected:
    FilesystemException();

public:
    explicit FilesystemException(const std::string& message);
    explicit FilesystemException(const char* message);
};


#endif // APP_EXCEPTIONS_H
