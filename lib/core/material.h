#ifndef MATERIAL_H
#define MATERIAL_H

#include "iprocess.h"
#include "collectionof.h"
#include "shader.h"
#include "texture.h"
#include "globaltransformation.h"

#include <memory>


class Material :
    public IProcess,
    public GlobalTransformation {
protected:
    std::shared_ptr<Shader> m_shader;
    CollectionOf<Texture> m_textures;

public:
    Material();
    virtual ~Material();

public:
    std::shared_ptr<Shader> GetShader();
    const std::shared_ptr<Shader> GetShader() const;
    void SetShader(const std::shared_ptr<Shader>& shader);

    CollectionOf<Texture>& GetTextures();
    const CollectionOf<Texture>& GetTextures() const;

protected:
    virtual void DoInitShader() = 0;

public: /* IProcess */
    void Processing() override;
};

#endif // MATERIAL_H
