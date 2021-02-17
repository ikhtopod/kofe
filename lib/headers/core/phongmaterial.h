#ifndef PHONGMATERIAL_H
#define PHONGMATERIAL_H

#include "material.h"
#include "color.h"

#include <filesystem>


class PhongMaterial : public Material {
protected:
    Color m_ambient;
    Color m_diffuse;
    Color m_specular;
    float m_shininess;

public:
    PhongMaterial(const PhongMaterial&) = delete;
    PhongMaterial(PhongMaterial&&) noexcept = delete;
    PhongMaterial& operator=(const PhongMaterial&) = delete;
    PhongMaterial& operator=(PhongMaterial&&) noexcept = delete;

public:
    PhongMaterial();
    virtual ~PhongMaterial() = default;

    explicit PhongMaterial(const Color& ambient, const Color& diffuse,
                           const Color& specular, float shininess);

public:
    Color GetAmbient() const;
    Color GetDiffuse() const;
    Color GetSpecular() const;
    float GetShininess() const;

    void SetAmbient(const Color& ambient);
    void SetDiffuse(const Color& diffuse);
    void SetSpecular(const Color& specular);
    void SetShininess(float shininess);

    void SetAmbientAndDiffuse(const Color& value);

    void SetAllParameters(const Color& ambient, const Color& diffuse,
                          const Color& specular, float shininess);

protected: /* Material */
    void DoInitShader() override;
};

#endif // PHONGMATERIAL_H
