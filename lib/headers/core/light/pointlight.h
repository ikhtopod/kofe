#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "light.h"


class PointLight : public Light {
protected:
    float m_ambient;
    float m_diffuse;
    float m_specular;
    float m_constant;
    float m_linear;
    float m_quadratic;

public:
    PointLight(const PointLight& other) = delete;
    PointLight(PointLight&& other) noexcept = delete;
    PointLight& operator=(const PointLight& other) = delete;
    PointLight& operator=(PointLight&& other) noexcept = delete;

public:
    PointLight();
    virtual ~PointLight();

    explicit PointLight(const Color& color);
    explicit PointLight(float ambient, float diffuse, float specular);

    explicit PointLight(float ambient, float diffuse, float specular,
                        float constant, float linear, float quadratic);

    explicit PointLight(const Color& color,
                        float ambient, float diffuse, float specular);

    explicit PointLight(const Color& color,
                        float ambient, float diffuse, float specular,
                        float constant, float linear, float quadratic);

public:
    float GetAmbient() const;
    float GetDiffuse() const;
    float GetSpecular() const;
    float GetConstant() const;
    float GetLinear() const;
    float GetQuadratic() const;

    Color GetAmbientColor() const;
    Color GetDiffuseColor() const;
    Color GetSpecularColor() const;

    void SetAmbient(float ambient);
    void SetDiffuse(float diffuse);
    void SetSpecular(float specular);
    void SetConstant(float constant);
    void SetLinear(float linear);
    void SetQuadratic(float quadratic);

    void SetADS(float ambient, float diffuse, float specular);
    void SetCLQ(float constant, float linear, float quadratic);
};

#endif // POINTLIGHT_H
