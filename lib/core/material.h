#ifndef MATERIAL_H
#define MATERIAL_H

#include "iprocess.h"
#include "collectionof.h"
#include "shader.h"


class Material : public IProcess {
private:
    CollectionOf<Shader> m_shaders;

public:
    Material();
    ~Material();
public:
    CollectionOf<Shader>& GetShaders();
    const CollectionOf<Shader>& GetShaders() const;

public: /* IProcess */
    void Processing() override;
};

#endif // MATERIAL_H
