#include "everywhere.h"


Everywhere::EverywherePtr<Window>& Everywhere::window() {
    return m_window;
}

const Everywhere::EverywherePtr<Window>& Everywhere::window() const {
    return m_window;
}

Everywhere::EverywherePtr<OpenGL>& Everywhere::openGL() {
    return m_opengl;
}

const Everywhere::EverywherePtr<OpenGL>& Everywhere::openGL() const {
    return m_opengl;
}

Everywhere::EverywherePtr<Input>& Everywhere::input() {
    return m_input;
}

const Everywhere::EverywherePtr<Input>& Everywhere::input() const {
    return m_input;
}

Everywhere::EverywherePtr<Space>& Everywhere::space() {
    return m_space;
}

const Everywhere::EverywherePtr<Space>& Everywhere::space() const {
    return m_space;
}
