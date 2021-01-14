#ifndef OPENGL_H
#define OPENGL_H

#include "iprocess.h"
#include "icanbeeverywhere.h"

#include <cstdint>
#include <string>


class OpenGL final :
        public IProcess,
        public ICanBeEverywhere
{
private:
    void InitOpenGL();
    void Init();

public:
    OpenGL(const OpenGL&) = delete;
    OpenGL(OpenGL&&) noexcept = delete;
    OpenGL& operator=(const OpenGL&) = delete;
    OpenGL& operator=(OpenGL&&) noexcept = delete;

    OpenGL();
    ~OpenGL() = default;

    void UpdateViewportSize() const;

public: /* IProcess */
    void Processing() override;

public:
    static std::string ToString();
};

#endif // OPENGL_H
