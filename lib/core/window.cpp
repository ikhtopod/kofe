#include "window.h"

#include "app_exceptions.h"
#include "everywhere.h"


void swap(Window& lhs, Window& rhs) {
    if (&lhs == &rhs) return;

    using std::swap;

    swap(lhs.m_context, rhs.m_context);
    swap(lhs.m_screen, rhs.m_screen);
    swap(lhs.m_title, rhs.m_title);
    swap(lhs.m_vSync, rhs.m_vSync);
}

bool Window::ContextIsValid() const { return m_context != nullptr; }

void Window::InitWindowHints() const {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 8);

    if (!m_vSync) {
        glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_FALSE);
    }

#if defined(__APPLE__) || defined(__MACH__)
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif
}

void Window::InitContext() {
    if (!glfwInit()) {
        throw WindowException { "Cannot init GLFW" };
    }

    InitWindowHints();

    m_context = glfwCreateWindow(m_screen.GetWidth(), m_screen.GetHeight(), m_title.c_str(), nullptr, nullptr);

    if (!ContextIsValid()) {
        throw WindowException { "Context is not valid" };
    }

    glfwMakeContextCurrent(m_context);

    if (m_vSync) {
        glfwSwapInterval(1);
    } else {
        glfwSwapInterval(0);
    }
}

Window::Window() :
    Window { ScreenSize { 800, 600 }, "[No Title]" } {}

Window::Window(ScreenSize screen, std::string title) :
    m_context { nullptr },
    m_screen { screen },
    m_title { title },
    m_vSync { true }
{
    InitContext();
}

Window::Window(Window&& other) noexcept :
    m_context { std::move(other.m_context) },
    m_screen { std::move(other.m_screen) },
    m_title { std::move(other.m_title) },
    m_vSync { std::move(other.m_vSync) }
{
    other.m_context = nullptr;
}

Window& Window::operator=(Window&& other) noexcept {
    if (this != &other) {
        m_context = std::move(other.m_context);
        other.m_context = nullptr;

        m_screen = std::move(other.m_screen);
        m_title = std::move(other.m_title);
        m_vSync = std::move(other.m_vSync);
    }

    return *this;
}

Window::~Window() {
    if (m_context)
        glfwDestroyWindow(m_context);
}

ScreenSize& Window::GetScreen() { return m_screen; }

GLFWwindow* Window::GetContext() { return m_context; }

void Window::SetContext(GLFWwindow* context) { m_context = context; }

std::string Window::GetTitle() const { return m_title; }

void Window::SetTitle(const std::string& title) { m_title = title; }

bool Window::CanProcess() {
    return glfwWindowShouldClose(m_context) == GLFW_FALSE;
}

void Window::SwapBuffers() {
    if (m_vSync) {
        glfwSwapBuffers(m_context);
    } else {
        Everywhere::Instance().Get<OpenGL>().Flush();
    }
}

void Window::Processing() {
    SwapBuffers();
}

std::string Window::ToString() {
    static const std::string CLASS_NAME { "Window" };
    return CLASS_NAME;
}
