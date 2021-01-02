#ifndef APPEXCEPTIONS_H
#define APPEXCEPTIONS_H

#include <exception>
#include <string>


class ApplicationException : public std::exception {
private:
    std::string m_message;

    ApplicationException();

public:
    explicit ApplicationException(const std::string& message);
    explicit ApplicationException(const char* message);

    const char* what() const noexcept override;
};


#endif // APPEXCEPTIONS_H
