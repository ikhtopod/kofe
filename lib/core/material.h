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
private: /* Default values */
    static const Color DEFAULT_COLOR;

private:
    CollectionOf<Shader> m_shaders;
    CollectionOf<Texture> m_textures;

    Color m_color;

public:
    Material();
    ~Material();

public:
    CollectionOf<Shader>& GetShaders();
    const CollectionOf<Shader>& GetShaders() const;

    CollectionOf<Texture>& GetTextures();
    const CollectionOf<Texture>& GetTextures() const;

private:
    void UniformMaterialData() const;

public: /* IProcess */
    void Processing() override;
};

#endif // MATERIAL_H
