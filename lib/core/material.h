#ifndef MATERIAL_H
#define MATERIAL_H

#include "iprocess.h"
#include "collectionof.h"
#include "shader.h"
#include "texture.h"
#include "globaltransformation.h"


class Material :
        public IProcess,
        public GlobalTransformation
{
private:
    CollectionOf<Shader> m_shaders;
    CollectionOf<Texture> m_textures;

public:
    Material();
    ~Material();

public:
    CollectionOf<Shader>& GetShaders();
    const CollectionOf<Shader>& GetShaders() const;

    CollectionOf<Texture>& GetTextures();
    const CollectionOf<Texture>& GetTextures() const;

public: /* IProcess */
    void Processing() override;
};

#endif // MATERIAL_H
