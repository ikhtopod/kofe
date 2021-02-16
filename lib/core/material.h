#ifndef MATERIAL_H
#define MATERIAL_H

#include "iprocess.h"
#include "collectionof.h"
#include "shader.h"
#include "globaltransformation.h"

#include <memory>


class Material :
    public IProcess,
    public GlobalTransformation {
protected:
    std::shared_ptr<Shader> m_shader;

public:
    Material(const Material&) = delete;
    Material(Material&&) noexcept = delete;
    Material& operator=(const Material&) = delete;
    Material& operator=(Material&&) noexcept = delete;

public:
    Material();
    virtual ~Material() = default;

    explicit Material(const std::shared_ptr<Shader>& shader);

public:
    std::shared_ptr<Shader> GetShader();
    const std::shared_ptr<Shader> GetShader() const;
    void SetShader(const std::shared_ptr<Shader>& shader);

protected:
    virtual void DoInitShader() = 0;

public: /* IProcess */
    void Processing() override;
};

#endif // MATERIAL_H
