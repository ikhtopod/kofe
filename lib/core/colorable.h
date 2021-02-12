#ifndef COLORABLE_H
#define COLORABLE_H

#include "color.h"


class Colorable {
protected:
    Color m_color;

public:
    friend void swap(Colorable&, Colorable&);

public:
    Colorable();
    Colorable(const Colorable& other);
    Colorable(Colorable&& other) noexcept;
    Colorable& operator=(const Colorable& other);
    Colorable& operator=(Colorable&& other) noexcept;
    virtual ~Colorable() = default;

public:
    explicit Colorable(const Color& color);
    explicit Colorable(Color&& color);

public:
    Color GetColor() const;
    void SetColor(const Color& color);
};


void swap(Colorable& lhs, Colorable& rhs);

#endif // COLORABLE_H
