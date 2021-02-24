#ifndef DELTATIME_H
#define DELTATIME_H

#include "interface/icanbeeverywhere.h"

#include <ratio>
#include <chrono>
#include <string>


class DeltaTime final : public ICanBeEverywhere {
    using Type = float;
    using Ratio = std::ratio<1>;
    using Duration = std::chrono::duration<Type, Ratio>;
    using Clock = std::chrono::steady_clock;
    using TimePoint = std::chrono::time_point<Clock, Duration>;

public:
    friend void swap(DeltaTime&, DeltaTime&);

private:
    TimePoint m_prevTime;
    Type m_delta;

public:
    DeltaTime();
    DeltaTime(const DeltaTime& other);
    DeltaTime(DeltaTime&& other) noexcept;
    DeltaTime& operator=(const DeltaTime& other);
    DeltaTime& operator=(DeltaTime&& other) noexcept;
    virtual ~DeltaTime() = default;

public:
    void Update();
    Type GetDelta() const;
    Type GetFPS() const;
};

void swap(DeltaTime& lhs, DeltaTime& rhs);

#endif // DELTATIME_H
