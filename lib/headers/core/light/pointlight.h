#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "light.h"


class PointLight : public Light {
protected:
    float m_radius;

    float m_ambient;
    float m_diffuse;
    float m_specular;

private: /* the values depend on the m_radius */
    float m_constant;
    float m_linear;
    float m_quadratic;

private:
    float m_linearInfluence;
    float m_quadraticInfluence;

public:
    PointLight(const PointLight& other) = delete;
    PointLight(PointLight&& other) noexcept = delete;
    PointLight& operator=(const PointLight& other) = delete;
    PointLight& operator=(PointLight&& other) noexcept = delete;

public:
    PointLight();
    virtual ~PointLight();

    explicit PointLight(const Color& color);
    explicit PointLight(float radius);
    explicit PointLight(const Color& color, float radius);
    explicit PointLight(float ambient, float diffuse, float specular);

    explicit PointLight(float radius,
                        float ambient, float diffuse, float specular);

    explicit PointLight(const Color& color,
                        float ambient, float diffuse, float specular);

    explicit PointLight(const Color& color, float radius,
                        float ambient, float diffuse, float specular);

public:
    float GetRadius() const;

    float GetAmbient() const;
    float GetDiffuse() const;
    float GetSpecular() const;

    float GetConstant() const;
    float GetLinear() const;
    float GetQuadratic() const;

    float GetLinearInfluence() const;
    float GetQuadraticInfluence() const;

    Color GetAmbientColor() const;
    Color GetDiffuseColor() const;
    Color GetSpecularColor() const;

    void SetRadius(float radius);

    void SetAmbient(float ambient);
    void SetDiffuse(float diffuse);
    void SetSpecular(float specular);

    void SetADS(float ambient, float diffuse, float specular);

    void SetLinearInfluence(float linearInfluence);
    void SetQuadraticInfluence(float quadraticInfluence);

private:
    void SetConstant(float constant);
    void SetLinear(float linear);
    void SetQuadratic(float quadratic);

    void SetCLQ(float constant, float linear, float quadratic);
    void UpdateCLQByRadius();
};

#endif // POINTLIGHT_H
