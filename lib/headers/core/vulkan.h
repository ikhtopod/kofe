#ifndef VULKAN_H
#define VULKAN_H

#include "graphics.h"


class Vulkan final : public Graphics {
public:
    Vulkan(const Vulkan&) = delete;
    Vulkan(Vulkan&&) noexcept = delete;
    Vulkan& operator=(const Vulkan&) = delete;
    Vulkan& operator=(Vulkan&&) noexcept = delete;

    Vulkan();
    ~Vulkan() = default;

protected: /* Graphics */
    void Init() override;

public: /* Graphics */
    void UpdateViewportSize() const override;
    void Flush() const override;

public: /* IProcess */
    void Processing() override;
};

#endif // VULKAN_H
