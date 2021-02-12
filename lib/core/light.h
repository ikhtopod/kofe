#ifndef LIGHT_H
#define LIGHT_H

#include "object.h"
#include "colorable.h"


class Light :
    public Object,
    public Colorable {
public:
    Light(const Light& other) = delete;
    Light(Light&& other) noexcept = delete;
    Light& operator=(const Light& other) = delete;
    Light& operator=(Light&& other) noexcept = delete;

public:
    Light();
    virtual ~Light() = default;

public:
    Color GetColor() const;
    void SetColor(const Color& color);

public: /* IProcess */
    void Processing() override;
};

#endif // LIGHT_H
