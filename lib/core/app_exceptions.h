#ifndef APPEXCEPTIONS_H
#define APPEXCEPTIONS_H

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

#endif // APPEXCEPTIONS_H
