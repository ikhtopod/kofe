#include "everywhere.h"


void Everywhere::InitWindow(Window* window) { m_window = window; }
Window& Everywhere::GetWindow() { return *m_window; }
void Everywhere::FreeWindow() { delete m_window; }

void Everywhere::InitOpenGL(OpenGL* opengl) { m_opengl = opengl; }
OpenGL& Everywhere::GetOpenGL() { return *m_opengl; }
void Everywhere::FreeOpenGL() { delete m_opengl; }
