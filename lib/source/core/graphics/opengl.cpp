#include "graphics/opengl.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "app_exceptions.h"
#include "everywhere.h"


void OpenGL::UpdateClearColor() {
    glClearColor(m_clearColor.Red(), m_clearColor.Green(),
                 m_clearColor.Blue(), m_clearColor.Alpha());
}

void OpenGL::InitOpenGL() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CCW);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    UpdateViewportSize();

    UpdateClearColor();
}

void OpenGL::Init() {
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        throw OpenGLException { "Cannot load OpenGL functions" };
    }

    InitOpenGL();
}

OpenGL::OpenGL() :
    Graphics {},
    m_clearColor { Color::BLACK } {
    Init();
}

void OpenGL::UpdateViewportSize() const {
    const ScreenSize& screen = Everywhere::Instance().Get<Window>().GetScreen();
    glViewport(0, 0, screen.GetWidth(), screen.GetHeight());
}

void OpenGL::Flush() const {
    glFlush();
}

void OpenGL::Processing() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

Color OpenGL::GetClearColor() const {
    return m_clearColor;
}

void OpenGL::SetClearColor(const Color& clearColor) {
    m_clearColor = clearColor;
    UpdateClearColor();
}
