#ifndef APPLICATION_H
#define APPLICATION_H

#include <string>


class Application final {
private:
    std::string m_title;

public:
    explicit Application(const std::string& title);
    explicit Application(const char* title);

    void Run();
};

#endif // APPLICATION_H
