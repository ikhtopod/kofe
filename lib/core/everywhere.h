#ifndef EVERYWHERE_H
#define EVERYWHERE_H

#include "singleton.h"
#include "window.h"


class Everywhere final : public Singleton<Everywhere> {
private:
    Window* m_window;

public:
    void InitWindow(Window* window);
    Window& GetWindow();
    void FreeWindow();
};

#endif // EVERYWHERE_H
