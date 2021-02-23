#include "misc/color.h"

#include <utility>
#include <limits>
#include <algorithm>


namespace {

using color_type = Color::color_type;

static constexpr color_type MIN_COLOR_VALUE { 0.0f };
static constexpr color_type MAX_COLOR_VALUE { 1.0f };

} // namespace


void swap(Color& lhs, Color& rhs) {
    if (&lhs == &rhs) return;

    using std::swap;

    swap(lhs.m_r, rhs.m_r);
    swap(lhs.m_g, rhs.m_g);
    swap(lhs.m_b, rhs.m_b);
    swap(lhs.m_a, rhs.m_a);
}


const Color
    Color::DEFAULT { 0.8f, 0.8f, 0.8f, 1.0f },
    Color::BLACK { ::MIN_COLOR_VALUE, ::MIN_COLOR_VALUE, ::MIN_COLOR_VALUE },
    Color::WHITE { ::MAX_COLOR_VALUE, ::MAX_COLOR_VALUE, ::MAX_COLOR_VALUE },
    Color::RED { ::MAX_COLOR_VALUE, ::MIN_COLOR_VALUE, ::MIN_COLOR_VALUE },
    Color::GREEN { ::MIN_COLOR_VALUE, ::MAX_COLOR_VALUE, ::MIN_COLOR_VALUE },
    Color::BLUE { ::MIN_COLOR_VALUE, ::MIN_COLOR_VALUE, ::MAX_COLOR_VALUE };


Color::Color() :
    Color { Color::BLACK } {}

Color::Color(const Color& other) :
    m_r { other.m_r },
    m_g { other.m_g },
    m_b { other.m_b },
    m_a { other.m_a } {}

Color::Color(Color&& other) noexcept :
    m_r { std::move(other.m_r) },
    m_g { std::move(other.m_g) },
    m_b { std::move(other.m_b) },
    m_a { std::move(other.m_a) } {}

Color& Color::operator=(const Color& other) {
    if (this != &other) {
        m_r = other.m_r;
        m_g = other.m_g;
        m_b = other.m_b;
        m_a = other.m_a;
    }

    return *this;
}

Color& Color::operator=(Color&& other) noexcept {
    if (this != &other) {
        m_r = std::move(other.m_r);
        m_g = std::move(other.m_g);
        m_b = std::move(other.m_b);
        m_a = std::move(other.m_a);
    }

    return *this;
}

Color::Color(const glm::vec3& rgb) :
    Color { rgb.r, rgb.g, rgb.b } {}

Color::Color(const glm::vec3& rgb, color_type a) :
    Color { rgb.r, rgb.g, rgb.b, a } {}

Color::Color(const glm::vec4& rgba) :
    Color { rgba.r, rgba.g, rgba.b, rgba.a } {}

Color::Color(color_type r, color_type g, color_type b) :
    Color { r, g, b, ::MAX_COLOR_VALUE } {}

Color::Color(color_type r, color_type g, color_type b, color_type a) {
    RGBA(r, g, b, a);
}

float Color::Clamp(color_type value) {
    return std::clamp<float>(value, ::MIN_COLOR_VALUE, ::MAX_COLOR_VALUE);
}

color_type Color::Red() const {
    return m_r;
}

color_type Color::Green() const {
    return m_g;
}

color_type Color::Blue() const {
    return m_b;
}

color_type Color::Alpha() const {
    return m_a;
}

void Color::Red(color_type r) {
    m_r = Clamp(r);
}

void Color::Green(color_type g) {
    m_g = Clamp(g);
}

void Color::Blue(color_type b) {
    m_b = Clamp(b);
}

void Color::Alpha(color_type a) {
    m_a = Clamp(a);
}

void Color::RGBA(color_type r, color_type g, color_type b, color_type a) {
    Red(r);
    Green(g);
    Blue(b);
    Alpha(a);
}

Color::operator glm::vec3() const {
    return { Red(), Green(), Blue() };
}

Color::operator glm::vec4() const {
    return { Red(), Green(), Blue(), Alpha() };
}
