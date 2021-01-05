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


class ShaderException : public ApplicationException {
protected:
    ShaderException();

public:
    explicit ShaderException(const std::string& message);
    explicit ShaderException(const char* message);

};


class TextureException : public ApplicationException {
protected:
    TextureException();

public:
    explicit TextureException(const std::string& message);
    explicit TextureException(const char* message);

};

#endif // APP_EXCEPTIONS_H
