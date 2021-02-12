#include "colorable.h"

#include <utility>


void swap(Colorable& lhs, Colorable& rhs) {
    if (&lhs == &rhs) return;

    using std::swap;

    swap(lhs.m_color, rhs.m_color);
}

Colorable::Colorable() :
    m_color {} {}


Colorable::Colorable(const Colorable& other) :
    m_color { other.m_color } {}


Colorable::Colorable(Colorable&& other) noexcept :
    m_color { std::move(other.m_color) } {}

Colorable& Colorable::operator=(const Colorable& other) {
    if (this != &other) {
        m_color = other.m_color;
    }

    return *this;
}

Colorable& Colorable::operator=(Colorable&& other) noexcept {
    if (this != &other) {
        m_color = std::move(other.m_color);
    }

    return *this;
}

Colorable::Colorable(const Color& color) :
    m_color { color } {}

Colorable::Colorable(Color&& color) :
    m_color { std::move(color) } {}

Color Colorable::GetColor() const {
    return m_color;
}

void Colorable::SetColor(const Color& color) {
    m_color = color;
}
