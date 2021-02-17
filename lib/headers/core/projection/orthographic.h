#ifndef ORTHOGRAPHIC_H
#define ORTHOGRAPHIC_H

#include "projection.h"


class Orthographic : public Projection {
    static const float BOTTOM;
    static const float TOP;
    static const float DEPTH_NEAR;
    static const float DEPTH_FAR;

private:
    glm::vec3 m_scale;

public:
    Orthographic(Orthographic&& other) noexcept = delete;
    Orthographic& operator=(Orthographic&& other) noexcept = delete;

    Orthographic();
    Orthographic(const Orthographic& other) = default;
    Orthographic& operator=(const Orthographic& other) = default;
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
