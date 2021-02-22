#ifndef TEXTUREMATERIAL_H
#define TEXTUREMATERIAL_H

#include "material.h"
#include "texture/texture.h"
#include "texture/texturedata.h"

#include <memory>


class TextureMaterial : public Material {
protected:
    TextureData m_diffuse;
    TextureData m_specular;
    TextureData m_emission;
    float m_shininess;

public:
    TextureMaterial(const TextureMaterial&) = delete;
    TextureMaterial(TextureMaterial&&) noexcept = delete;
    TextureMaterial& operator=(const TextureMaterial&) = delete;
    TextureMaterial& operator=(TextureMaterial&&) noexcept = delete;

public:
    TextureMaterial();
    virtual ~TextureMaterial() = default;

    explicit TextureMaterial(const TextureData& diffuse,
                             const TextureData& specular,
                             const TextureData& emission);

    explicit TextureMaterial(const TextureData& diffuse,
                             const TextureData& specular,
                             const TextureData& emission,
                             float shininess);

public:
    std::shared_ptr<Texture> GetDiffuse() const;
    std::shared_ptr<Texture> GetSpecular() const;
    std::shared_ptr<Texture> GetEmission() const;

    TextureData GetDiffuseTextureData() const;
    TextureData GetSpecularTextureData() const;
    TextureData GetEmissionTextureData() const;

    void SetDiffuseTextureData(const TextureData& diffuse);
    void SetSpecularTextureData(const TextureData& specular);
    void SetEmissionTextureData(const TextureData& emission);

    float GetShininess() const;
    void SetShininess(float shininess);

protected: /* Material */
    void DoInitShader() override;

public: /* IProcess */
    void Processing() override;
};

#endif // TEXTUREMATERIAL_H
