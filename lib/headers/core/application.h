#ifndef APPLICATION_H
#define APPLICATION_H

#include "app_exceptions.h"
#include "space/space.h"

#include <string>


class Application final {
public:
    Application();
    explicit Application(const char* title);
    explicit Application(const std::string& title);
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

private: /* Temp Methods */
    Space* CreateDemoSpace();
    void DemoMainLoop();
};

#endif // APPLICATION_H
