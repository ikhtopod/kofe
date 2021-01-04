#ifndef INPUT_H
#define INPUT_H

#include "iprocess.h"

#include <GLFW/glfw3.h>


class Input final : public IProcess {
private: /* Callback */
    class Callback final {
    public:
        Callback() = delete;
        Callback(const Callback&) = delete;
        Callback(Callback&&) noexcept = delete;
        Callback& operator=(const Callback&) = delete;
        Callback& operator=(Callback&&) noexcept = delete;
        ~Callback() = delete;

    public:
        static void Assign();

    private:
        static void FramebufferSizeCallback(GLFWwindow*, int width, int height);
    };

private:
    void Init();

private:
    void KeyEvents();

public:
    Input();

public: /* IProcess */
    void Processing() override;
};

#endif // INPUT_H
