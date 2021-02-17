#include "opengl.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "app_exceptions.h"
#include "everywhere.h"


const Color OpenGL::CLEAR_COLOR { 0.05f, 0.0f, 0.1f, 1.0f };


void OpenGL::InitOpenGL() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CCW);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    UpdateViewportSize();

    glClearColor(CLEAR_COLOR.Red(), CLEAR_COLOR.Green(),
                 CLEAR_COLOR.Blue(), CLEAR_COLOR.Alpha());
}

void OpenGL::Init() {
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        throw OpenGLException { "Cannot load OpenGL functions" };
    }

    InitOpenGL();
}

OpenGL::OpenGL() {
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
