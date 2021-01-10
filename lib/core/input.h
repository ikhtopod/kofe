#ifndef INPUT_H
#define INPUT_H

#include "iprocess.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Input final : public IProcess {
private: /* Callbacks */
    static void FramebufferSizeCallback(GLFWwindow*, int width, int height);

private:
    void Init();

private:
    void AssignCallbacks();
    void KeyEvents();

public:
    Input();

public: /* IProcess */
    void Processing() override;
};

#endif // INPUT_H
