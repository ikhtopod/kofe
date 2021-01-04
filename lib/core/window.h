#ifndef WINDOW_H
#define WINDOW_H

#include <utility>
#include <string>

#include "screensize.h"

#include <GLFW/glfw3.h>


class Window final {
private:
    GLFWwindow* m_context;
    ScreenSize m_screen;
    std::string m_title;

public:
    friend void swap(Window&, Window&);

private:
    bool ContextIsValid() const;

    void InitWindowHints() const;
    void InitContext();

public:
    Window();
    explicit Window(ScreenSize screen, std::string title);

    Window(Window&& other) noexcept;
    Window& operator=(Window&& other) noexcept;
    ~Window();

public:
    Window(const Window& other) = delete;
    Window& operator=(const Window& other) = delete;

public:
    ScreenSize& GetScreen();

    GLFWwindow* GetContext();
    void SetContext(GLFWwindow* context);

    std::string GetTitle() const;
    void SetTitle(const std::string& title);

public:
    bool CanProcess();
    void SwapBuffers();
};

void swap(Window& lhs, Window& rhs);

#endif // WINDOW_H
