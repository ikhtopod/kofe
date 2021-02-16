#ifndef MATERIAL_H
#define MATERIAL_H

#include "iprocess.h"
#include "collectionof.h"
#include "shader.h"
#include "texture.h"
#include "globaltransformation.h"
#include "color.h"

#include <string>


class Material :
    public IProcess,
    public GlobalTransformation {
protected:
    std::shared_ptr<Shader> m_shader;
    CollectionOf<Texture> m_textures;
    Color m_color;

public:
    Material();
    virtual ~Material();

public:
    std::shared_ptr<Shader> GetShader();
    const std::shared_ptr<Shader> GetShader() const;
    void SetShader(const std::shared_ptr<Shader>& shader);

    CollectionOf<Texture>& GetTextures();
    const CollectionOf<Texture>& GetTextures() const;

    Color GetColor() const;
    void SetColor(const Color& color);

protected:
    virtual void InitShader();

public: /* IProcess */
    void Processing() override;
};

#endif // MATERIAL_H
