#ifndef OPENGL_H
#define OPENGL_H

#include "irendered.h"


class OpenGL final : public IRendered {
private:
    void InitOpenGL();
    void Init();

public:
    OpenGL();

public: /* IRendered */
    void Rendering() override;
};

#endif // OPENGL_H
