#ifndef POINTLIGHTMATERIAL_H
#define POINTLIGHTMATERIAL_H

#include "material.h"


class PointLightMaterial : public Material {
protected: /* Material */
    void InitShader() override;
};

#endif // POINTLIGHTMATERIAL_H