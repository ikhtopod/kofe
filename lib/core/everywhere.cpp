#include "everywhere.h"


void Everywhere::InitWindow(Window* window) { m_window = window; }
Window& Everywhere::GetWindow() { return *m_window; }
void Everywhere::FreeWindow() { delete m_window; }

void Everywhere::InitOpenGL(OpenGL* opengl) { m_opengl = opengl; }
OpenGL& Everywhere::GetOpenGL() { return *m_opengl; }
void Everywhere::FreeOpenGL() { delete m_opengl; }

void Everywhere::InitInput(Input* input) { m_input = input; }
Input& Everywhere::GetInput() { return *m_input; }
void Everywhere::FreeInput() { delete m_input; }

void Everywhere::InitSpace(Space* space) { m_space = space; }
Space& Everywhere::GetSpace() { return *m_space; }
void Everywhere::FreeSpace() { delete m_space; }
