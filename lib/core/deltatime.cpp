#include "deltatime.h"

#include <utility>


void swap(DeltaTime& lhs, DeltaTime& rhs) {
    if (&lhs == &rhs) return;

    using std::swap;
    swap(lhs.m_prevTime, rhs.m_prevTime);
    swap(lhs.m_delta, rhs.m_delta);
}


DeltaTime::DeltaTime() :
    m_prevTime { DeltaTime::Clock::now() },
    m_delta {} {}

DeltaTime::DeltaTime(const DeltaTime& other) :
    m_prevTime { other.m_prevTime },
    m_delta { other.m_delta } {}

DeltaTime::DeltaTime(DeltaTime&& other) noexcept :
    m_prevTime { std::move(other.m_prevTime) },
    m_delta { std::move(other.m_delta) } {}

DeltaTime& DeltaTime::operator=(const DeltaTime& other) {
    if (this != &other) {
        m_prevTime = other.m_prevTime;
        m_delta = other.m_delta;
    }

    return *this;
}

DeltaTime& DeltaTime::operator=(DeltaTime&& other) noexcept {
    if (this != &other) {
        m_prevTime = std::move(other.m_prevTime);
        m_delta = std::move(other.m_delta);
    }

    return *this;
}

void DeltaTime::Update() {
    DeltaTime::TimePoint currentTime { DeltaTime::Clock::now() };
    m_delta = (currentTime - m_prevTime).count();
    m_prevTime = currentTime;
}

DeltaTime::Type DeltaTime::GetDelta() const {
    return m_delta;
}
