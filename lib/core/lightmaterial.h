#ifndef LIGHTMATERIAL_H
#define LIGHTMATERIAL_H

#include "material.h"
#include "color.h"


class LightMaterial : public Material {
protected:
    Color m_color;

public:
    Color GetColor() const;
    void SetColor(const Color& color);

protected: /* Material */
    void DoInitShader() override;
};

#endif // LIGHTMATERIAL_H
