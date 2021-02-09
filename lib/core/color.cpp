#include "color.h"

#include <utility>
#include <limits>


const uint8_t Color::RED { 0 };
const uint8_t Color::GREEN { 1 };
const uint8_t Color::BLUE { 2 };
const uint8_t Color::ALPHA { 3 };

void swap(Color& lhs, Color& rhs) {
    if (&lhs == &rhs) return;

    using std::swap;

    swap(lhs.m_id, rhs.m_id);
}

Color::Color() : Color { 0 } {}

Color::Color(const Color& other) :
    Color { other.m_id } {}

Color::Color(Color&& other) noexcept :
    Color { std::move(other.m_id) } {}

Color& Color::operator=(const Color& other) {
    if (this != &other) {
        m_id = other.m_id;
    }

    return *this;
}

Color& Color::operator=(Color&& other) noexcept {
    if (this != &other) {
        m_id = std::move(other.m_id);
    }

    return *this;
}

Color::Color(uint32_t id) :
    m_id { id } {}

Color::Color(uint8_t r, uint8_t g, uint8_t b) :
    Color {r, g, b, std::numeric_limits<uint8_t>::max()} {}

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    RGBA(r, g, b, a);
}

uint32_t Color::Id() const {
    return m_id;
}

void Color::Id(uint32_t id) {
    m_id = id;
}

uint8_t Color::Red() const {
    return (&m_chanel)[RED];
}

uint8_t Color::Green() const {
    return (&m_chanel)[GREEN];
}

uint8_t Color::Blue() const {
    return (&m_chanel)[BLUE];
}

uint8_t Color::Alpha() const {
    return (&m_chanel)[ALPHA];
}

void Color::Red(uint8_t r) {
    (&m_chanel)[RED] = r;
}

void Color::Green(uint8_t g) {
    (&m_chanel)[GREEN] = g;
}

void Color::Blue(uint8_t b) {
    (&m_chanel)[BLUE] = b;
}

void Color::Alpha(uint8_t a) {
    (&m_chanel)[ALPHA] = a;
}

void Color::RGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
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
