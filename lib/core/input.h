#ifndef INPUT_H
#define INPUT_H

#include "icanbeeverywhere.h"
#include "iprocess.h"
#include "inputobserver.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <string>


class Input final :
        public IProcess,
        public ICanBeEverywhere,
        public ObservableInput
{
private:
    static Input* GetThisInput();

private: /* Callbacks */
    static void FramebufferSizeCallback(GLFWwindow*, int width, int height);
    static void ScrollCallback(GLFWwindow*, double x, double y);
    static void MousePositionCallback(GLFWwindow*, double x, double y);

private:
    GLFWwindow* context;

    glm::vec2 m_mousePosition;
    glm::vec2 m_scrollValue;

private:
    void Init();

private:
    void AssignCallbacks();
    void KeyEvents();
    void UpdateContext();

private:
    void SetMousePosition(const glm::vec2& mousePosition);
    void SetMousePosition(glm::vec2&& mousePosition) noexcept;

    void SetScrollValue(const glm::vec2& scrollValue);
    void SetScrollValue(glm::vec2&& scrollValue) noexcept;

public:
    Input(const Input&) = delete;
    Input(Input&&) noexcept = delete;
    Input& operator=(const Input&) = delete;
    Input& operator=(Input&&) noexcept = delete;

    Input();
    ~Input() = default;

public:
    glm::vec2 GetMousePosition() const;
    glm::vec2 GetScrollValue() const;

    bool MouseButtonIsReleased(int key) const;
    bool MouseButtonIsPressed(int key) const;

    bool KeyIsReleased(int key) const;
    bool KeyIsPressed(int key) const;


public: /* IProcess */
    void Processing() override;
};

#endif // INPUT_H
