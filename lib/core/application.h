#ifndef APPLICATION_H
#define APPLICATION_H

#include <string>


class Application final {
public:
    Application();
    explicit Application(const std::string& title);
    explicit Application(const char* title);
    ~Application();

public:
    Application(const Application&) = delete;
    Application(Application&&) noexcept = delete;
    Application& operator=(const Application&) = delete;
    Application& operator=(Application&&) noexcept = delete;

private:
    void MainLoop();

public:
    void Run();
};

#endif // APPLICATION_H
