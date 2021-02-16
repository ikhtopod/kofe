#ifndef TEXTUREMATERIAL_H
#define TEXTUREMATERIAL_H

#include "material.h"
#include "texture.h"

#include <memory>


class TextureMaterial : public Material {
protected:
    std::shared_ptr<Texture> m_diffuse;
    std::shared_ptr<Texture> m_specular;
    float m_shininess;

public:
    TextureMaterial(const TextureMaterial&) = delete;
    TextureMaterial(TextureMaterial&&) noexcept = delete;
    TextureMaterial& operator=(const TextureMaterial&) = delete;
    TextureMaterial& operator=(TextureMaterial&&) noexcept = delete;

public:
    TextureMaterial();
    virtual ~TextureMaterial() = default;

    explicit TextureMaterial(const std::shared_ptr<Texture>& diffuse,
                             const std::shared_ptr<Texture>& specular);

    explicit TextureMaterial(const std::shared_ptr<Texture>& diffuse,
                             const std::shared_ptr<Texture>& specular,
                             float shininess);

public:
    std::shared_ptr<Texture> GetDiffuse() const;
    std::shared_ptr<Texture> GetSpecular() const;
    float GetShininess() const;

    void SetDiffuse(const std::shared_ptr<Texture>& diffuse);
    void SetSpecular(const std::shared_ptr<Texture>& specular);
    void SetShininess(float shininess);

protected: /* Material */
    void DoInitShader() override;

public: /* IProcess */
    void Processing() override;
};

#endif // TEXTUREMATERIAL_H
