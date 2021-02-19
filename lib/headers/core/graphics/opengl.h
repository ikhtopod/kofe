#ifndef OPENGL_H
#define OPENGL_H

#include "graphics.h"
#include "misc/color.h"


class OpenGL final : public Graphics {
private:
    Color m_clearColor;

private:
    void UpdateClearColor();
    void InitOpenGL();

public:
    OpenGL(const OpenGL&) = delete;
    OpenGL(OpenGL&&) noexcept = delete;
    OpenGL& operator=(const OpenGL&) = delete;
    OpenGL& operator=(OpenGL&&) noexcept = delete;

public:
    OpenGL();
    ~OpenGL() = default;

public:
    Color GetClearColor() const;
    void SetClearColor(const Color& clearColor);

protected: /* Graphics */
    void Init() override;

public: /* Graphics */
    void UpdateViewportSize() const override;
    void Flush() const override;

public: /* IProcess */
    void Processing() override;
};

#endif // OPENGL_H
