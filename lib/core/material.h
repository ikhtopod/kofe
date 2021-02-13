#ifndef MATERIAL_H
#define MATERIAL_H

#include "iprocess.h"
#include "collectionof.h"
#include "shader.h"
#include "texture.h"
#include "globaltransformation.h"
#include "colorable.h"

#include <string>


class Material :
    public IProcess,
    public GlobalTransformation,
    public Colorable {
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

private:
    void UniformMaterialData(std::shared_ptr<Shader>& shader);
    void UniformLightData(std::shared_ptr<Shader>& shader);
    void UniformCameraData(std::shared_ptr<Shader>& shader);

    void AdditionalUniformData(std::shared_ptr<Shader>& shader);

public: /* IProcess */
    void Processing() override;
};

#endif // MATERIAL_H
