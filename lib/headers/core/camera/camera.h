#ifndef CAMERA_H
#define CAMERA_H

#include "interface/icanbeeverywhere.h"
#include "interface/icanbematrix.h"
#include "input/inputobserver.h"
#include "transform/localtransformation.h"
#include "misc/axis.h"

#include <glm/gtx/quaternion.hpp>


class Camera :
    public ICanBeEverywhere,
    public ICanBeMatrix,
    public IInputObserver,
    public LocalTransformation {
protected:
    static const float DEFAULT_FOV;

    static const float DEFAULT_MOVEMENT_SPEED;

    static const float DEFAULT_PITCH;
    static const float MIN_PITCH;
    static const float MAX_PITCH;

    static const float DEFAULT_YAW;
    static const float MIN_YAW;
    static const float MAX_YAW;

    static const float DEFAULT_ROLL;

    static const float DEFAULT_MOUSE_SENSITIVITY_YAW;
    static const float DEFAULT_MOUSE_SENSITIVITY_PITCH;

    static const glm::quat DEFAULT_CAMERA_ORIENTATION;

private:
    float m_fov;

protected:
    glm::vec2 m_lastMousePosition;
    Axis m_axis;

    float m_yaw;
    float m_pitch;

public:
    Camera(const Camera&) = delete;
    Camera(Camera&&) noexcept = delete;
    Camera& operator=(const Camera&) = delete;
    Camera& operator=(Camera&&) noexcept = delete;

public:
    Camera();
    virtual ~Camera();

protected:
    void UpdateCameraVectors();

public:
    float GetFoV() const;

public: /* ICanBeMatrix */
    glm::mat4 ToMatrix() const override;
};

#endif // CAMERA_H
