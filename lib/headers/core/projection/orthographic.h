#ifndef ORTHOGRAPHIC_H
#define ORTHOGRAPHIC_H

#include "projection.h"


class Orthographic : public Projection {
protected:
    glm::vec3 m_scale;

public:
    Orthographic(Orthographic&& other) noexcept = delete;
    Orthographic& operator=(Orthographic&& other) noexcept = delete;

    Orthographic();
    Orthographic(const Orthographic& other);
    Orthographic& operator=(const Orthographic& other);
    virtual ~Orthographic() = default;

    explicit Orthographic(const glm::vec3& scale);
    explicit Orthographic(glm::vec3&& scale) noexcept;
    explicit Orthographic(float distance);

public:
    glm::vec3 GetScale() const;
    void SetScale(const glm::vec3& scale);
    void SetScale(glm::vec3&& scale) noexcept;
    void SetScaleByDistance(float distance);

public: /* Projection */
    glm::mat4 ToMatrix() const override;
};

#endif // ORTHOGRAPHIC_H
