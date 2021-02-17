#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include "light.h"


class DirectionalLight : public Light {
protected:
    float m_ambient;
    float m_diffuse;
    float m_specular;

public:
    DirectionalLight(const DirectionalLight& other) = delete;
    DirectionalLight(DirectionalLight&& other) noexcept = delete;
    DirectionalLight& operator=(const DirectionalLight& other) = delete;
    DirectionalLight& operator=(DirectionalLight&& other) noexcept = delete;

public:
    DirectionalLight();
    virtual ~DirectionalLight();

    explicit DirectionalLight(const Color& color);
    explicit DirectionalLight(float ambient, float diffuse, float specular);

    explicit DirectionalLight(const Color& color, float ambient,
                              float diffuse, float specular);

public:
    float GetAmbient() const;
    float GetDiffuse() const;
    float GetSpecular() const;

    Color GetAmbientColor() const;
    Color GetDiffuseColor() const;
    Color GetSpecularColor() const;

    void SetAmbient(float ambient);
    void SetDiffuse(float diffuse);
    void SetSpecular(float specular);
};

#endif // DIRECTIONALLIGHT_H
