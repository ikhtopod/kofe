#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "interface/icanbematrix.h"
#include "misc/axis.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include <ostream>
#include <string>


class Transform final : public ICanBeMatrix {
public:
    friend void swap(Transform& lhs, Transform& rhs);
    friend std::ostream& operator<<(std::ostream&, const Transform&);

private:
    glm::vec3 m_position;
    glm::quat m_orientation;
    glm::vec3 m_scale;

    Axis m_axis;
    glm::quat m_axisOrientation;

private:
    Transform(const glm::vec3& position,
              const glm::quat& orientation,
              const glm::vec3& scale,
              const Axis& axis,
              const glm::quat& axisOrientation);

    Transform(glm::vec3&& position,
              glm::quat&& orientation,
              glm::vec3&& scale,
              Axis&& axis,
              glm::quat&& axisOrientation) noexcept;

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

    Transform(const glm::mat4& matrix);

    Transform& operator+=(const Transform& other);

    explicit operator std::string() const;

public:
    void Reset();

    glm::vec3 GetPosition() const;
    void SetPosition(const glm::vec3& position);
    void AddPosition(const glm::vec3& position);

    glm::quat GetOrientation() const;
    void SetOrientation(const glm::quat& orientation);
    void SetOrientation(float angle, const glm::vec3& axis);
    void AddOrientation(const glm::quat& orientation);
    void AddOrientation(float angle, const glm::vec3& axis);

    glm::vec3 GetRotation() const;
    void SetRotation(const glm::vec3& rotation);
    void AddRotation(const glm::vec3& rotation);

    glm::vec3 GetScale() const;
    void SetScale(const glm::vec3& scale);
    void AddScale(const glm::vec3& scale);

    Axis GetAxis() const;
    glm::quat GetAxisOrientation() const;
    void SetAxisOrientation(const glm::quat& axisOrientation);

private:
    void UpdateAxisByAxisOrientation();

public:
    glm::mat4 GetPositionMatrix() const;
    glm::mat4 GetOrientationMatrix() const;
    glm::mat4 GetScaleMatrix() const;

public: /* ICanBeMatrix */
    glm::mat4 ToMatrix() const override;

public: /* Additional rotation methods */
    void AddRotationX(float x);
    void AddRotationY(float y);
    void AddRotationZ(float z);

    void AddRotationXY(float x, float y);
    void AddRotationXZ(float x, float z);
    void AddRotationYX(float y, float x);
    void AddRotationYZ(float y, float z);
    void AddRotationZX(float z, float x);
    void AddRotationZY(float z, float y);

    void AddRotationXYZ(float x, float y, float z);
    void AddRotationXZY(float x, float z, float y);
    void AddRotationYXZ(float y, float x, float z);
    void AddRotationYZX(float y, float z, float x);
    void AddRotationZXY(float z, float x, float y);
    void AddRotationZYX(float z, float y, float x);

    void AddRotationX(const glm::vec3& rot);
    void AddRotationY(const glm::vec3& rot);
    void AddRotationZ(const glm::vec3& rot);

    void AddRotationXY(const glm::vec3& rot);
    void AddRotationXZ(const glm::vec3& rot);
    void AddRotationYX(const glm::vec3& rot);
    void AddRotationYZ(const glm::vec3& rot);
    void AddRotationZX(const glm::vec3& rot);
    void AddRotationZY(const glm::vec3& rot);

    void AddRotationXYZ(const glm::vec3& rot);
    void AddRotationXZY(const glm::vec3& rot);
    void AddRotationYXZ(const glm::vec3& rot);
    void AddRotationYZX(const glm::vec3& rot);
    void AddRotationZXY(const glm::vec3& rot);
    void AddRotationZYX(const glm::vec3& rot);

public: /* Additional position methods */
    void AddPositionX(float x);
    void AddPositionY(float y);
    void AddPositionZ(float z);

    void AddPositionXY(float x, float y);
    void AddPositionXZ(float x, float z);
    void AddPositionYZ(float y, float z);

    void AddPositionXYZ(float x, float y, float z);
};


Transform operator+(Transform lhs, const Transform& rhs);
std::ostream& operator<<(std::ostream& out, const Transform& rhs);

void swap(Transform& lhs, Transform& rhs);

Transform MatrixToTransform(const glm::mat4& matrix);

#endif // TRANSFORM_H
