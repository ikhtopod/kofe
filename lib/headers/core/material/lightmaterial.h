#ifndef LIGHTMATERIAL_H
#define LIGHTMATERIAL_H

#include "material.h"
#include "misc/color.h"


class LightMaterial : public Material {
protected:
    Color m_color;

public:
    LightMaterial(const LightMaterial&) = delete;
    LightMaterial(LightMaterial&&) noexcept = delete;
    LightMaterial& operator=(const LightMaterial&) = delete;
    LightMaterial& operator=(LightMaterial&&) noexcept = delete;

public:
    LightMaterial();
    virtual ~LightMaterial() = default;

    explicit LightMaterial(const Color& color);

public:
    Color GetColor() const;
    void SetColor(const Color& color);

protected: /* Material */
    void DoInitShader() override;
};

#endif // LIGHTMATERIAL_H
