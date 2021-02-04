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
    swap(lhs.m_orientation, rhs.m_orientation);
    swap(lhs.m_scale, rhs.m_scale);
}


const glm::vec3 Transform::DEFAULT_POSITION { 0.0f };
const glm::vec3 Transform::DEFAULT_ROTATION { 0.0f };
const glm::quat Transform::DEFAULT_ORIENTATION {};
const glm::vec3 Transform::DEFAULT_SCALE { 1.0f };


Transform MatrixToTransform(const glm::mat4& matrix) {
    glm::vec3 scale;
    glm::quat orientation;
    glm::vec3 translation;
    [[maybe_unused]] glm::vec3 skew;
    [[maybe_unused]] glm::vec4 perspective;

    glm::decompose(matrix, scale, orientation, translation, skew, perspective);

    return { translation, orientation, scale };
}

Transform::Transform() :
    Transform { DEFAULT_POSITION,
                DEFAULT_ORIENTATION,
                DEFAULT_SCALE } {}

Transform::Transform(const Transform& other) :
    Transform { other.m_position,
                other.m_orientation,
                other.m_scale } {}

Transform::Transform(Transform&& other) noexcept :
    Transform { std::move(other.m_position),
                std::move(other.m_orientation),
                std::move(other.m_scale) } {}

Transform& Transform::operator=(const Transform& other) {
    if (this != &other) {
        m_position = other.m_position;
        m_orientation = other.m_orientation;
        m_scale = other.m_scale;
    }

    return *this;
}

Transform& Transform::operator=(Transform&& other) noexcept {
    if (this != &other) {
        m_position = std::move(other.m_position);
        m_orientation = std::move(other.m_orientation);
        m_scale = std::move(other.m_scale);
    }

    return *this;
}

Transform::Transform(const glm::vec3& position,
                     const glm::quat& orientation,
                     const glm::vec3& scale) :
    m_position { position },
    m_orientation { orientation },
    m_scale { scale } {}

Transform::Transform(glm::vec3&& position,
                     glm::quat&& orientation,
                     glm::vec3&& scale) noexcept :
    m_position { std::move(position) },
    m_orientation { std::move(orientation) },
    m_scale { std::move(scale) } {}

Transform::Transform(const glm::mat4& matrix) :
    Transform { MatrixToTransform(matrix) } {}

Transform::Transform(glm::mat4&& matrix) noexcept :
    Transform { MatrixToTransform(matrix) } {}

Transform& Transform::operator+=(const Transform& other) {
    glm::mat4 matrix =
            GetPositionMatrix() * other.GetPositionMatrix() *
            GetOrientationMatrix() * other.GetOrientationMatrix() *
            GetScaleMatrix() * other.GetScaleMatrix();

    Transform tmp = MatrixToTransform(matrix);

    SetPosition(tmp.GetPosition());
    SetOrientation(tmp.GetOrientation());
    SetScale(tmp.GetScale());

    return *this;
}

Transform operator+(Transform lhs, const Transform& rhs) {
    return lhs += rhs;
}

void Transform::Reset() {
    *this = Transform {};
}

glm::vec3 Transform::GetPosition() const {
    return m_position;
}

void Transform::SetPosition(const glm::vec3& position) {
    m_position = position;
}

void Transform::AddPosition(const glm::vec3& position) {
    m_position += position;
}

glm::quat Transform::GetOrientation() const {
    return m_orientation;
}

void Transform::SetOrientation(const glm::quat& orientation) {
    m_orientation = orientation;
}

void Transform::SetOrientation(float angle, const glm::vec3& axis) {
    m_orientation = glm::angleAxis(glm::radians(angle), glm::normalize(axis));
}

void Transform::AddOrientation(const glm::quat& orientation) {
    m_orientation = glm::normalize(orientation * m_orientation);
}

void Transform::AddOrientation(float angle, const glm::vec3& axis) {
    AddOrientation(glm::angleAxis(glm::radians(angle), glm::normalize(axis)));
}

glm::vec3 Transform::GetRotation() const {
    return glm::degrees(glm::eulerAngles(m_orientation));
}

void Transform::SetRotation(const glm::vec3& rotation) {
    m_orientation = glm::quat(glm::radians(rotation));
}

void Transform::AddRotation(const glm::vec3& rotation) {
    m_orientation = glm::normalize(glm::quat(glm::radians(rotation)) * m_orientation);
}

glm::vec3 Transform::GetScale() const {
    return m_scale;
}

void Transform::SetScale(const glm::vec3& scale) {
    m_scale = scale;
}

void Transform::AddScale(const glm::vec3& scale) {
    m_scale *= scale;
}

glm::mat4 Transform::GetPositionMatrix() const {
    return glm::translate(m_position);
}

glm::mat4 Transform::GetOrientationMatrix() const {
    return glm::mat4_cast(m_orientation);
}

glm::mat4 Transform::GetScaleMatrix() const {
    return glm::scale(m_scale);
}

glm::mat4 Transform::ToMatrix() const {
    return GetPositionMatrix() * GetOrientationMatrix() * GetScaleMatrix();
}
