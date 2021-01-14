#ifndef EVERYWHERE_H
#define EVERYWHERE_H

#include "singleton.h"
#include "window.h"
#include "opengl.h"
#include "input.h"
#include "space.h"


class Everywhere final : public Singleton<Everywhere> {
    template <typename T>
    class EverywherePtr final {
    private:
        T* m_value;

    public:
        EverywherePtr(const EverywherePtr&) = delete;
        EverywherePtr(EverywherePtr&&) noexcept = delete;
        EverywherePtr& operator=(const EverywherePtr&) = delete;
        EverywherePtr& operator=(EverywherePtr&&) noexcept = delete;

        EverywherePtr() : m_value {} {}
        ~EverywherePtr() = default;

        void Init(T* value) { m_value = value; }
        T& Get() { return *m_value; }
        const T& Get() const { return *m_value; }
        void Free() { delete m_value; }
    };

private:
    EverywherePtr<Window> m_window;
    EverywherePtr<OpenGL> m_opengl;
    EverywherePtr<Input> m_input;
    EverywherePtr<Space> m_space;

public:
    EverywherePtr<Window>& window();
    const EverywherePtr<Window>& window() const;

    EverywherePtr<OpenGL>& openGL();
    const EverywherePtr<OpenGL>& openGL() const;

    EverywherePtr<Input>& input();
    const EverywherePtr<Input>& input() const;

    EverywherePtr<Space>& space();
    const EverywherePtr<Space>& space() const;
};


#endif // EVERYWHERE_H
