#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>


class Transform final {
    static const glm::vec3 DEFAULT_POSITION;
    static const glm::vec3 DEFAULT_ROTATION;
    static const glm::vec3 DEFAULT_SCALE;

public:
    friend void swap(Transform& lhs, Transform& rhs);

private:
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;

public:
    Transform();
    Transform(const Transform& other);
    Transform(Transform&& other) noexcept;
    Transform& operator=(const Transform& other);
    Transform& operator=(Transform&& other) noexcept;
    ~Transform() = default;

    Transform(const glm::vec3& position,
              const glm::vec3& rotation,
              const glm::vec3& scale);

    Transform(glm::vec3&& position,
              glm::vec3&& rotation,
              glm::vec3&& scale) noexcept;

    Transform(const glm::mat4& matrix);
    Transform(glm::mat4&& matrix) noexcept;

public:
    void Reset();

    glm::vec3 GetPosition() const;
    void SetPosition(const glm::vec3& position);

    glm::vec3 GetRotation() const;
    void SetRotation(const glm::vec3& rotation);

    glm::vec3 GetScale() const;
    void SetScale(const glm::vec3& scale);

public:
    glm::mat4 GetPositionMatrix() const;
    glm::mat4 GetRotationMatrix() const;
    glm::mat4 GetScaleMatrix() const;

    glm::mat4 ToMatrix() const;
};


void swap(Transform& lhs, Transform& rhs);


Transform MatrixToTransform(const glm::mat4& matrix);

#endif // TRANSFORM_H
