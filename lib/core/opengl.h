#ifndef OPENGL_H
#define OPENGL_H

#include "iprocess.h"

#include <cstdint>


class OpenGL final : public IProcess {
private:
    void InitOpenGL();
    void Init();

public:
    OpenGL();

    void UpdateViewportSize() const;

public: /* IProcess */
    void Processing() override;
};

#endif // OPENGL_H
