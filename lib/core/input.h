#ifndef INPUT_H
#define INPUT_H

#include "icanbeeverywhere.h"
#include "iprocess.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>


class Input final :
        public IProcess,
        public ICanBeEverywhere
{
private: /* Callbacks */
    static void FramebufferSizeCallback(GLFWwindow*, int width, int height);

private:
    void Init();

private:
    void AssignCallbacks();
    void KeyEvents();

public:
    Input(const Input&) = delete;
    Input(Input&&) noexcept = delete;
    Input& operator=(const Input&) = delete;
    Input& operator=(Input&&) noexcept = delete;

    Input();
    ~Input() = default;

public: /* IProcess */
    void Processing() override;
};

#endif // INPUT_H
