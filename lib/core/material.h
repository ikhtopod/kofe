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
    CollectionOf<Shader> m_shaders;
    CollectionOf<Texture> m_textures;
    Color m_color;

public:
    Material();
    virtual ~Material();

public:
    CollectionOf<Shader>& GetShaders();
    const CollectionOf<Shader>& GetShaders() const;

    CollectionOf<Texture>& GetTextures();
    const CollectionOf<Texture>& GetTextures() const;

    Color GetColor() const;
    void SetColor(const Color& color);

protected:
    virtual void InitShaders();

public: /* IProcess */
    void Processing() override;
};

#endif // MATERIAL_H
