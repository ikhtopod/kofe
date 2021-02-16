#ifndef DEFAULTMATERIAL_H
#define DEFAULTMATERIAL_H

#include "material.h"
#include "color.h"


class DefaultMaterial : public Material {
protected:
    Color m_color;

public:
    DefaultMaterial();
    virtual ~DefaultMaterial() = default;

public:
    Color GetColor() const;
    void SetColor(const Color& color);

protected: /* Material */
    void DoInitShader() override;
};

#endif // DEFAULTMATERIAL_H
