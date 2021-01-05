#ifndef EVERYWHERE_H
#define EVERYWHERE_H

#include "singleton.h"
#include "window.h"
#include "opengl.h"
#include "input.h"
#include "space.h"


class Everywhere final : public Singleton<Everywhere> {
private:
    Window* m_window;
    OpenGL* m_opengl;
    Input* m_input;
    Space* m_space;

public:
    void InitWindow(Window* window);
    Window& GetWindow();
    void FreeWindow();

    void InitOpenGL(OpenGL* opengl);
    OpenGL& GetOpenGL();
    void FreeOpenGL();

    void InitInput(Input* input);
    Input& GetInput();
    void FreeInput();

    void InitSpace(Space* space);
    Space& GetSpace();
    void FreeSpace();
};


#endif // EVERYWHERE_H
