#include "transform.h"

#include "axis.h"

#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <utility>


void swap(Transform& lhs, Transform& rhs) {
    if (&lhs == &rhs) return;

    using std::swap;

    swap(lhs.m_position, rhs.m_position);
    swap(lhs.m_rotation, rhs.m_rotation);
    swap(lhs.m_scale, rhs.m_scale);
}


const glm::vec3 Transform::DEFAULT_POSITION { 0.0f };
const glm::vec3 Transform::DEFAULT_ROTATION { 0.0f };
const glm::vec3 Transform::DEFAULT_SCALE { 1.0f };


glm::vec3 QuaternionToVector_Degrees(const glm::quat& quaternion) {
    return glm::degrees(glm::eulerAngles(quaternion));
}

Transform MatrixToTransform(const glm::mat4& matrix) {
    glm::vec3 scale;
    glm::quat orientation;
    glm::vec3 translation;
    [[maybe_unused]] glm::vec3 skew;
    [[maybe_unused]] glm::vec4 perspective;

    glm::decompose(matrix, scale, orientation, translation, skew, perspective);

    return { translation, QuaternionToVector_Degrees(orientation), scale };
}

Transform::Transform() :
    Transform { DEFAULT_POSITION,
                DEFAULT_ROTATION,
                DEFAULT_SCALE } {}

Transform::Transform(const Transform& other) :
    Transform { other.m_position,
                other.m_rotation,
                other.m_scale } {}

Transform::Transform(Transform&& other) noexcept :
    Transform { std::move(other.m_position),
                std::move(other.m_rotation),
                std::move(other.m_scale) } {}

Transform& Transform::operator=(const Transform& other) {
    if (this != &other) {
        m_position = other.m_position;
        m_rotation = other.m_rotation;
        m_scale = other.m_scale;
    }

    return *this;
}

Transform& Transform::operator=(Transform&& other) noexcept {
    if (this != &other) {
        m_position = std::move(other.m_position);
        m_rotation = std::move(other.m_rotation);
        m_scale = std::move(other.m_scale);
    }

    return *this;
}

Transform::Transform(const glm::vec3& position,
                     const glm::vec3& rotation,
                     const glm::vec3& scale) :
    m_position { position },
    m_rotation { rotation },
    m_scale { scale } {}

Transform::Transform(glm::vec3&& position,
                     glm::vec3&& rotation,
                     glm::vec3&& scale) noexcept :
    m_position { std::move(position) },
    m_rotation { std::move(rotation) },
    m_scale { std::move(scale) } {}

Transform::Transform(const glm::mat4& matrix) :
    Transform { MatrixToTransform(matrix) } {}

Transform::Transform(glm::mat4&& matrix) noexcept :
    Transform { MatrixToTransform(matrix) } {}

void Transform::Reset() {
    *this = Transform {};
}

glm::vec3 Transform::GetPosition() const {
    return m_position;
}

void Transform::SetPosition(const glm::vec3& position) {
    m_position = position;
}

glm::vec3 Transform::GetRotation() const {
    return m_rotation;
}

void Transform::SetRotation(const glm::vec3& rotation) {
    m_rotation = rotation;
}

glm::vec3 Transform::GetScale() const {
    return m_scale;
}

void Transform::SetScale(const glm::vec3& scale) {
    m_scale = scale;
}

glm::mat4 Transform::GetPositionMatrix() const {
    return glm::translate(m_position);
}

glm::mat4 Transform::GetRotationMatrix() const {
    glm::mat4 rotX = glm::rotate(glm::radians(m_rotation.x), Axis::RIGHT);
    glm::mat4 rotY = glm::rotate(glm::radians(m_rotation.y), Axis::UP);
    glm::mat4 rotZ = glm::rotate(glm::radians(m_rotation.z), Axis::FRONT);

    return rotX * rotY * rotZ;
}

glm::mat4 Transform::GetScaleMatrix() const {
    return glm::scale(glm::mat4 {}, m_scale);
}

glm::mat4 Transform::ToMatrix() const {
    return GetPositionMatrix() * GetRotationMatrix() * GetScaleMatrix();
}
