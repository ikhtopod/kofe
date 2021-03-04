#ifndef TEXTUREMATERIAL_H
#define TEXTUREMATERIAL_H

#include "material.h"
#include "texture/texture.h"
#include "texture/textureparams.h"

#include <memory>


class TextureMaterial : public Material {
protected:
    TextureParams m_diffuse;
    TextureParams m_specular;
    TextureParams m_emission;
    float m_shininess;

public:
    TextureMaterial(const TextureMaterial&) = delete;
    TextureMaterial(TextureMaterial&&) noexcept = delete;
    TextureMaterial& operator=(const TextureMaterial&) = delete;
    TextureMaterial& operator=(TextureMaterial&&) noexcept = delete;

public:
    TextureMaterial();
    virtual ~TextureMaterial() = default;

    explicit TextureMaterial(const TextureParams& diffuse,
                             const TextureParams& specular,
                             const TextureParams& emission);

    explicit TextureMaterial(const TextureParams& diffuse,
                             const TextureParams& specular,
                             const TextureParams& emission,
                             float shininess);

public:
    std::shared_ptr<Texture> GetDiffuse() const;
    std::shared_ptr<Texture> GetSpecular() const;
    std::shared_ptr<Texture> GetEmission() const;

    TextureParams GetDiffuseTextureParams() const;
    TextureParams GetSpecularTextureParams() const;
    TextureParams GetEmissionTextureParams() const;

    void SetDiffuseTextureParams(const TextureParams& diffuse);
    void SetSpecularTextureParams(const TextureParams& specular);
    void SetEmissionTextureParams(const TextureParams& emission);

    float GetShininess() const;
    void SetShininess(float shininess);

protected: /* Material */
    void DoInitShader() override;

public: /* IProcess */
    void Processing() override;
};

#endif // TEXTUREMATERIAL_H
