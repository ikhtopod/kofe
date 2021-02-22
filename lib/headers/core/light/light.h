#ifndef LIGHT_H
#define LIGHT_H

#include "object/object.h"
#include "mesh/mesh.h"
#include "misc/color.h"

#include <memory>


class Light : public Object {
public:
    Light(const Light& other) = delete;
    Light(Light&& other) noexcept = delete;
    Light& operator=(const Light& other) = delete;
    Light& operator=(Light&& other) noexcept = delete;

protected:
    Color m_color;
    std::shared_ptr<Mesh> m_childMesh;

public:
    Light();
    virtual ~Light() = default;

    explicit Light(const Color& color);

public:
    Color GetColor() const;
    void SetColor(const Color& color);

public: /* IProcess */
    void Processing() override;
};

#endif // LIGHT_H
