#ifndef EVERYWHERE_H
#define EVERYWHERE_H

#include "singleton.h"
#include "window.h"
#include "opengl.h"


class Everywhere final : public Singleton<Everywhere> {
private:
    Window* m_window;
    OpenGL* m_opengl;

public:
    void InitWindow(Window* window);
    Window& GetWindow();
    void FreeWindow();

    void InitOpenGL(OpenGL* opengl);
    OpenGL& GetOpenGL();
    void FreeOpenGL();
};

#endif // EVERYWHERE_H
