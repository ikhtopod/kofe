#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>


class Transform final {
    static const glm::vec3 DEFAULT_POSITION;
    static const glm::vec3 DEFAULT_ROTATION;
    static const glm::quat DEFAULT_ORIENTATION;
    static const glm::vec3 DEFAULT_SCALE;

public:
    friend void swap(Transform& lhs, Transform& rhs);

private:
    glm::vec3 m_position;
    glm::quat m_orientation;
    glm::vec3 m_scale;

public:
    Transform();
    Transform(const Transform& other);
    Transform(Transform&& other) noexcept;
    Transform& operator=(const Transform& other);
    Transform& operator=(Transform&& other) noexcept;
    ~Transform() = default;

    Transform(const glm::vec3& position,
              const glm::quat& orientation,
              const glm::vec3& scale);

    Transform(glm::vec3&& position,
              glm::quat&& orientation,
              glm::vec3&& scale) noexcept;

    Transform(const glm::mat4& matrix);
    Transform(glm::mat4&& matrix) noexcept;

    Transform& operator+=(const Transform& other);

public:
    void Reset();

    glm::vec3 GetPosition() const;
    void SetPosition(const glm::vec3& position);
    void AddPosition(const glm::vec3& position);

    glm::quat GetOrientation() const;
    void SetOrientation(const glm::quat& orientation);
    void SetOrientation(float angle, const glm::vec3& rotation);
    void AddOrientation(const glm::quat& orientation);
    void AddOrientation(float angle, const glm::vec3& rotation);

    glm::vec3 GetRotation() const;
    void SetRotation(const glm::vec3& rotation);
    void AddRotation(const glm::vec3& rotation);

    glm::vec3 GetScale() const;
    void SetScale(const glm::vec3& scale);
    void AddScale(const glm::vec3& scale);

public:
    glm::mat4 GetPositionMatrix() const;
    glm::mat4 GetOrientationMatrix() const;
    glm::mat4 GetScaleMatrix() const;

    glm::mat4 ToMatrix() const;
};


Transform operator+(Transform lhs, const Transform& rhs);

void swap(Transform& lhs, Transform& rhs);

glm::vec3 QuaternionToVector_Degrees(const glm::quat& quaternion);
Transform MatrixToTransform(const glm::mat4& matrix);

#endif // TRANSFORM_H
