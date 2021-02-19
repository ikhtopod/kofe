#include "misc/axis.h"

#include <utility>
#include <sstream>


void swap(Axis& lhs, Axis& rhs) {
    if (&lhs == &rhs) return;

    using std::swap;

    swap(lhs.m_right, rhs.m_right);
    swap(lhs.m_up, rhs.m_up);
    swap(lhs.m_front, rhs.m_front);
}


const glm::vec3 Axis::X { glm::vec3 { 1.0f, 0.0f, 0.0f } };
const glm::vec3 Axis::Y { glm::vec3 { 0.0f, 1.0f, 0.0f } };
const glm::vec3 Axis::Z { glm::vec3 { 0.0f, 0.0f, 1.0f } };

const glm::vec3 Axis::RIGHT { Axis::X };
const glm::vec3 Axis::PITCH { Axis::X };

const glm::vec3 Axis::UP { Axis::Y };
const glm::vec3 Axis::YAW { Axis::Y };

const glm::vec3 Axis::FORWARD { Axis::Z };
const glm::vec3 Axis::FRONT { Axis::Z };
const glm::vec3 Axis::ROLL { Axis::Z };

const glm::vec3 Axis::LEFT { -Axis::RIGHT };
const glm::vec3 Axis::DOWN { -Axis::UP };
const glm::vec3 Axis::BACK { -Axis::FRONT };
const glm::vec3 Axis::BACKWARD { -Axis::FORWARD };

Axis::Axis() :
    Axis { RIGHT, UP, FRONT } {}

Axis::Axis(const Axis& other) :
    Axis { other.m_right,
           other.m_up,
           other.m_front } {}

Axis::Axis(Axis&& other) noexcept :
    Axis { std::move(other.m_right),
           std::move(other.m_up),
           std::move(other.m_front) } {}

Axis& Axis::operator=(const Axis& other) {
    if (this != &other) {
        m_right = other.m_right;
        m_up = other.m_up;
        m_front = other.m_front;
    }

    return *this;
}

Axis& Axis::operator=(Axis&& other) noexcept {
    if (this != &other) {
        m_right = std::move(other.m_right);
        m_up = std::move(other.m_up);
        m_front = std::move(other.m_front);
    }

    return *this;
}

Axis::Axis(const glm::vec3& right,
           const glm::vec3& up,
           const glm::vec3& front) :
    m_right { right },
    m_up { up },
    m_front { front } {}

Axis::Axis(glm::vec3&& right,
           glm::vec3&& up,
           glm::vec3&& front) noexcept :
    m_right { std::move(right) },
    m_up { std::move(up) },
    m_front { std::move(front) } {}

glm::vec3 Axis::GetRight() const {
    return m_right;
}

Axis::operator std::string() const {
    std::stringstream result {};

    const glm::vec3 right = GetRight();
    const glm::vec3 up = GetUp();
    const glm::vec3 front = GetFront();

    result << "Right { x: " << right.x << ", y: " << right.y
           << ", z: " << right.z << " }\n";
    result << "Up { x: " << up.x << ", y: " << up.y
           << ", z: " << up.z << " }\n";
    result << "Front { x: " << front.x << ", y: " << front.y
           << ", z: " << front.z << " }";

    return result.str();
}

std::ostream& operator<<(std::ostream& out, const Axis& rhs) {
    return out << static_cast<std::string>(rhs);
}

void Axis::SetRight(const glm::vec3& right) {
    m_right = right;
}

glm::vec3 Axis::GetUp() const {
    return m_up;
}

void Axis::SetUp(const glm::vec3& up) {
    m_up = up;
}

glm::vec3 Axis::GetFront() const {
    return m_front;
}

void Axis::SetFront(const glm::vec3& front) {
    m_front = front;
}
