#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include "light.h"


class SpotLight : public Light {
protected:
    float m_radius;
    float m_cutoffAsRadians;
    float m_outerCutoffAsRadians;

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
    SpotLight(const SpotLight& other) = delete;
    SpotLight(SpotLight&& other) noexcept = delete;
    SpotLight& operator=(const SpotLight& other) = delete;
    SpotLight& operator=(SpotLight&& other) noexcept = delete;

public:
    SpotLight();
    virtual ~SpotLight();

    explicit SpotLight(const Color& color);
    explicit SpotLight(float radius, float cutoffAsDegrees);
    explicit SpotLight(const Color& color, float radius, float cutoffAsDegrees);
    explicit SpotLight(float ambient, float diffuse, float specular);

    explicit SpotLight(float radius, float cutoffAsDegrees,
                       float ambient, float diffuse, float specular);

    explicit SpotLight(const Color& color,
                       float ambient, float diffuse, float specular);

    explicit SpotLight(const Color& color, float radius, float cutoffAsDegrees,
                       float ambient, float diffuse, float specular);

public:
    float GetRadius() const;
    float GetCutoffDegrees() const;
    float GetCutoffRadians() const;

    float GetOuterCutoffRadians() const;

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
    void SetCutoffDegrees(float cutoffAsDegrees);
    void SetCutoffRadians(float cutoffAsRadians);

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
    void UpdateOuterCutoff();
};

#endif // SPOTLIGHT_H
