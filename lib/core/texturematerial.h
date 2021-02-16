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
protected: /* Material */
    void DoInitShader() override;

public: /* IProcess */
    void Processing() override;
};

#endif // TEXTUREMATERIAL_H
