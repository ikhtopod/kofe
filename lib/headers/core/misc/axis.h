#ifndef AXIS_H
#define AXIS_H

#include <glm/glm.hpp>


class Axis final {
public:
    static const glm::vec3 X;
    static const glm::vec3 Y;
    static const glm::vec3 Z;

    static const glm::vec3 RIGHT;
    static const glm::vec3 PITCH;

    static const glm::vec3 UP;
    static const glm::vec3 YAW;

    static const glm::vec3 FRONT;
    static const glm::vec3 FORWARD;
    static const glm::vec3 ROLL;

    static const glm::vec3 LEFT;
    static const glm::vec3 DOWN;
    static const glm::vec3 BACK;
    static const glm::vec3 BACKWARD;

private:
    glm::vec3 m_right;
    glm::vec3 m_up;
    glm::vec3 m_front;

public:
    friend void swap(Axis&, Axis&);

public:
    Axis();
    Axis(const Axis& other);
    Axis(Axis&& other) noexcept;
    Axis& operator=(const Axis& other);
    Axis& operator=(Axis&& other) noexcept;
    ~Axis() = default;

    Axis(const glm::vec3& right,
         const glm::vec3& up,
         const glm::vec3& front);

    Axis(glm::vec3&& right,
         glm::vec3&& up,
         glm::vec3&& front) noexcept;

public:
    glm::vec3 GetRight() const;
    void SetRight(const glm::vec3& right);

    glm::vec3 GetUp() const;
    void SetUp(const glm::vec3& up);

    glm::vec3 GetFront() const;
    void SetFront(const glm::vec3& front);
};


void swap(Axis& lhs, Axis& rhs);

#endif // AXIS_H
