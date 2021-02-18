#include "misc/screensize.h"


void swap(ScreenSize& lhs, ScreenSize& rhs) {
    if (&lhs == &rhs) return;

    using std::swap;

    swap(lhs.m_width, rhs.m_width);
    swap(lhs.m_height, rhs.m_height);
}


ScreenSize::ScreenSize() :
    m_width { 0 },
    m_height { 0 } {}

ScreenSize::ScreenSize(const ScreenSize& other) :
    m_width { other.m_width },
    m_height { other.m_height } {}

ScreenSize::ScreenSize(ScreenSize&& other) noexcept :
    m_width { std::move(other.m_width) },
    m_height { std::move(other.m_height) } {}

ScreenSize& ScreenSize::operator=(const ScreenSize& other) {
    ScreenSize tmp { other };
    swap(*this, tmp);
    return *this;
}

ScreenSize& ScreenSize::operator=(ScreenSize&& other) noexcept {
    if (this != &other) {
        m_width = std::move(other.m_width);
        m_height = std::move(other.m_height);
    }

    return *this;
}

ScreenSize::ScreenSize(int32_t size) :
    m_width { size },
    m_height { size } {}

ScreenSize::ScreenSize(int32_t width, int32_t height) :
    m_width { width },
    m_height { height } {}

void ScreenSize::Update(int32_t width, int32_t height) {
    m_width = width;
    m_height = height;
}

void ScreenSize::Update(ScreenSize other) {
    swap(*this, other);
}

int32_t ScreenSize::GetWidth() const {
    return m_width;
}

void ScreenSize::SetWidth(const int32_t width) {
    m_width = width;
}

int32_t ScreenSize::GetHeight() const {
    return m_height;
}

void ScreenSize::SetHeight(const int32_t height) {
    m_height = height;
}
