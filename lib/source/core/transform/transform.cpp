#include "transform/transform.h"

#include "misc/axis.h"

#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <utility>
#include <sstream>


namespace {

static const glm::vec3 DEFAULT_POSITION { 0.0f };
static const glm::vec3 DEFAULT_ROTATION { 0.0f };
static const glm::vec3 DEFAULT_SCALE { 1.0f };
static const glm::quat DEFAULT_ORIENTATION { 1.0f, 0.0f, 0.0f, 0.0f };
static const glm::quat DEFAULT_AXIS_ORIENTATION { 0.0f, 0.0f, 0.0f, 1.0f };

} // namespace

void swap(Transform& lhs, Transform& rhs) {
    if (&lhs == &rhs) return;

    using std::swap;

    swap(lhs.m_position, rhs.m_position);
    swap(lhs.m_orientation, rhs.m_orientation);
    swap(lhs.m_scale, rhs.m_scale);
    swap(lhs.m_axis, rhs.m_axis);
    swap(lhs.m_axisOrientation, rhs.m_axisOrientation);
}

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
                other.m_scale,
                other.m_axis,
                other.m_axisOrientation } {}

Transform::Transform(Transform&& other) noexcept :
    Transform { std::move(other.m_position),
                std::move(other.m_orientation),
                std::move(other.m_scale),
                std::move(other.m_axis),
                std::move(other.m_axisOrientation) } {}

Transform::Transform(const glm::vec3& position,
                     const glm::quat& orientation,
                     const glm::vec3& scale) :
    Transform { position,
                orientation,
                scale,
                Axis {},
                DEFAULT_AXIS_ORIENTATION } {}

Transform::Transform(const glm::mat4& matrix) :
    Transform { MatrixToTransform(matrix) } {}

Transform::Transform(const glm::vec3& position,
                     const glm::quat& orientation,
                     const glm::vec3& scale,
                     const Axis& axis,
                     const glm::quat& axisOrientation) :
    m_position { position },
    m_orientation { orientation },
    m_scale { scale },
    m_axis { axis },
    m_axisOrientation { axisOrientation } {
    UpdateAxisByAxisOrientation();
}

Transform::Transform(glm::vec3&& position,
                     glm::quat&& orientation,
                     glm::vec3&& scale,
                     Axis&& axis,
                     glm::quat&& axisOrientation) noexcept :
    m_position { std::move(position) },
    m_orientation { std::move(orientation) },
    m_scale { std::move(scale) },
    m_axis { std::move(axis) },
    m_axisOrientation { std::move(axisOrientation) } {
    UpdateAxisByAxisOrientation();
}

Transform& Transform::operator=(const Transform& other) {
    if (this != &other) {
        m_position = other.m_position;
        m_orientation = other.m_orientation;
        m_scale = other.m_scale;
        m_axis = other.m_axis;
        m_axisOrientation = other.m_axisOrientation;
    }

    return *this;
}

Transform& Transform::operator=(Transform&& other) noexcept {
    if (this != &other) {
        m_position = std::move(other.m_position);
        m_orientation = std::move(other.m_orientation);
        m_scale = std::move(other.m_scale);
        m_axis = std::move(other.m_axis);
        m_axisOrientation = std::move(other.m_axisOrientation);
    }

    return *this;
}

Transform& Transform::operator+=(const Transform& other) {
    const glm::quat axisOrientation = m_axisOrientation;

    *this = MatrixToTransform(ToMatrix() * other.ToMatrix());

    SetAxisOrientation(axisOrientation);
    // UpdateAxisByAxisOrientation();

    return *this;
}

Transform operator+(Transform lhs, const Transform& rhs) {
    return lhs += rhs;
}

Transform::operator std::string() const {
    std::stringstream result {};

    const glm::vec3 pos = GetPosition();
    const glm::vec3 rot = GetRotation();
    const glm::quat orient = GetOrientation();
    const glm::vec3 scale = GetScale();
    const glm::quat axisOrient = GetAxisOrientation();

    result << "Transform:\n";
    result << "  Position { x: " << pos.x << ", y: " << pos.y
           << ", z: " << pos.z << " }\n";
    result << "  Rotation { x: " << rot.x << ", y: " << rot.y
           << ", z: " << rot.z << " }\n";
    result << "  Orientation { x: " << orient.x << ", y: " << orient.y
           << ", z: " << orient.z << ", w: " << orient.w << " }\n";
    result << "  Scale { x: " << scale.x << ", y: " << scale.y
           << ", z: " << scale.z << " }\n";
    result << m_axis;
    result << "\nAxisOrientation: { x: " << axisOrient.x << ", y: " << axisOrient.y
           << ", z: " << axisOrient.z << ", w: " << axisOrient.w << " }";

    return result.str();
}

std::ostream& operator<<(std::ostream& out, const Transform& rhs) {
    return out << static_cast<std::string>(rhs);
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
    m_orientation = glm::normalize(orientation);
    UpdateAxisByAxisOrientation();
}

void Transform::SetOrientation(float angle, const glm::vec3& axis) {
    m_orientation = glm::angleAxis(glm::radians(angle), glm::normalize(axis));
    UpdateAxisByAxisOrientation();
}

void Transform::AddOrientation(const glm::quat& orientation) {
    m_orientation = orientation * m_orientation;
    UpdateAxisByAxisOrientation();
}

void Transform::AddOrientation(float angle, const glm::vec3& axis) {
    AddOrientation(glm::angleAxis(glm::radians(angle), glm::normalize(axis)));
    // UpdateAxisByAxisOrientation();
}

glm::vec3 Transform::GetRotation() const {
    return glm::degrees(glm::eulerAngles(m_orientation));
}

void Transform::SetRotation(const glm::vec3& rotation) {
    m_orientation = glm::quat(glm::radians(rotation));
    UpdateAxisByAxisOrientation();
}

void Transform::AddRotation(const glm::vec3& rotation) {
    m_orientation = glm::normalize(glm::quat(glm::radians(rotation)) * m_orientation);
    UpdateAxisByAxisOrientation();
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

Axis Transform::GetAxis() const {
    return m_axis;
}

glm::quat Transform::GetAxisOrientation() const {
    return m_axisOrientation;
}

void Transform::SetAxisOrientation(const glm::quat& axisOrientation) {
    m_axisOrientation = axisOrientation;

    UpdateAxisByAxisOrientation();
}

void Transform::UpdateAxisByAxisOrientation() {
    const glm::quat ORIENTATION_FRONT =
            GetOrientation() * m_axisOrientation * glm::conjugate(GetOrientation());

    m_axis.SetFront(glm::normalize(
            glm::vec3 { ORIENTATION_FRONT.x, ORIENTATION_FRONT.y, ORIENTATION_FRONT.z }));
    m_axis.SetRight(glm::normalize(glm::cross(m_axis.GetFront(), Axis::UP)));
    m_axis.SetUp(glm::normalize(glm::cross(m_axis.GetRight(), m_axis.GetFront())));
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

/* Additional rotation methods */

void Transform::AddRotationX(float x) {
    AddRotation({ x, 0.0f, 0.0f });
}

void Transform::AddRotationY(float y) {
    AddRotation({ 0.0f, y, 0.0f });
}

void Transform::AddRotationZ(float z) {
    AddRotation({ 0.0f, 0.0f, z });
}

void Transform::AddRotationXY(float x, float y) {
    AddRotation({ x, 0.0f, 0.0f });
    AddRotation({ 0.0f, y, 0.0f });
}

void Transform::AddRotationXZ(float x, float z) {
    AddRotation({ x, 0.0f, 0.0f });
    AddRotation({ 0.0f, 0.0f, z });
}

void Transform::AddRotationYX(float y, float x) {
    AddRotation({ 0.0f, y, 0.0f });
    AddRotation({ x, 0.0f, 0.0f });
}

void Transform::AddRotationYZ(float y, float z) {
    AddRotation({ 0.0f, y, 0.0f });
    AddRotation({ 0.0f, 0.0f, z });
}

void Transform::AddRotationZX(float z, float x) {
    AddRotation({ 0.0f, 0.0f, z });
    AddRotation({ x, 0.0f, 0.0f });
}

void Transform::AddRotationZY(float z, float y) {
    AddRotation({ 0.0f, 0.0f, z });
    AddRotation({ 0.0f, y, 0.0f });
}

void Transform::AddRotationXYZ(float x, float y, float z) {
    AddRotation({ x, 0.0f, 0.0f });
    AddRotation({ 0.0f, y, 0.0f });
    AddRotation({ 0.0f, 0.0f, z });
}

void Transform::AddRotationXZY(float x, float z, float y) {
    AddRotation({ x, 0.0f, 0.0f });
    AddRotation({ 0.0f, 0.0f, z });
    AddRotation({ 0.0f, y, 0.0f });
}

void Transform::AddRotationYXZ(float y, float x, float z) {
    AddRotation({ 0.0f, y, 0.0f });
    AddRotation({ x, 0.0f, 0.0f });
    AddRotation({ 0.0f, 0.0f, z });
}

void Transform::AddRotationYZX(float y, float z, float x) {
    AddRotation({ 0.0f, y, 0.0f });
    AddRotation({ 0.0f, 0.0f, z });
    AddRotation({ x, 0.0f, 0.0f });
}

void Transform::AddRotationZXY(float z, float x, float y) {
    AddRotation({ 0.0f, 0.0f, z });
    AddRotation({ x, 0.0f, 0.0f });
    AddRotation({ 0.0f, y, 0.0f });
}

void Transform::AddRotationZYX(float z, float y, float x) {
    AddRotation({ 0.0f, 0.0f, z });
    AddRotation({ 0.0f, y, 0.0f });
    AddRotation({ x, 0.0f, 0.0f });
}

void Transform::AddRotationX(const glm::vec3& rot) {
    AddRotationX(rot.x);
}

void Transform::AddRotationY(const glm::vec3& rot) {
    AddRotationY(rot.y);
}

void Transform::AddRotationZ(const glm::vec3& rot) {
    AddRotationZ(rot.z);
}

void Transform::AddRotationXY(const glm::vec3& rot) {
    AddRotationXY(rot.x, rot.y);
}

void Transform::AddRotationXZ(const glm::vec3& rot) {
    AddRotationXZ(rot.x, rot.z);
}

void Transform::AddRotationYX(const glm::vec3& rot) {
    AddRotationYX(rot.y, rot.x);
}

void Transform::AddRotationYZ(const glm::vec3& rot) {
    AddRotationYZ(rot.y, rot.z);
}

void Transform::AddRotationZX(const glm::vec3& rot) {
    AddRotationZX(rot.z, rot.x);
}

void Transform::AddRotationZY(const glm::vec3& rot) {
    AddRotationZY(rot.z, rot.y);
}

void Transform::AddRotationXYZ(const glm::vec3& rot) {
    AddRotationXYZ(rot.x, rot.y, rot.z);
}

void Transform::AddRotationXZY(const glm::vec3& rot) {
    AddRotationXZY(rot.x, rot.z, rot.y);
}

void Transform::AddRotationYXZ(const glm::vec3& rot) {
    AddRotationYXZ(rot.y, rot.x, rot.z);
}

void Transform::AddRotationYZX(const glm::vec3& rot) {
    AddRotationYZX(rot.y, rot.z, rot.x);
}

void Transform::AddRotationZXY(const glm::vec3& rot) {
    AddRotationZXY(rot.z, rot.x, rot.y);
}

void Transform::AddRotationZYX(const glm::vec3& rot) {
    AddRotationZYX(rot.z, rot.y, rot.x);
}
