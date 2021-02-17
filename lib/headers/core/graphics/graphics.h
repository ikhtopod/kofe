#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "interface/iprocess.h"
#include "interface/icanbeeverywhere.h"


class Graphics :
    public IProcess,
    public ICanBeEverywhere {
public:
    Graphics(const Graphics&) = delete;
    Graphics(Graphics&&) noexcept = delete;
    Graphics& operator=(const Graphics&) = delete;
    Graphics& operator=(Graphics&&) noexcept = delete;

public:
    Graphics() = default;
    virtual ~Graphics() = default;

protected:
    virtual void Init() = 0;

public:
    virtual void UpdateViewportSize() const = 0;
    virtual void Flush() const = 0;
};

#endif // GRAPHICS_H
