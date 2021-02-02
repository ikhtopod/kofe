#ifndef CAMERA_H
#define CAMERA_H

#include "icanbeeverywhere.h"
#include "icanbematrix.h"
#include "inputobserver.h"
#include "localtransformation.h"
#include "axis.h"


class Camera :
        public ICanBeEverywhere,
        public ICanBeMatrix,
        public IInputObserver,
        public LocalTransformation
{
private:
    static const float DEFAULT_FOV;

protected:
    static const float DEFAULT_MOVEMENT_SPEED;

    static const float DEFAULT_PITCH;
    static const float MAX_PITCH;
    static const float MIN_PITCH;

    static const float DEFAULT_YAW;
    static const float MIN_YAW;
    static const float MAX_YAW;

    static const float DEFAULT_ROLL;

    static const float DEFAULT_MOUSE_SENSITIVITY_X;
    static const float DEFAULT_MOUSE_SENSITIVITY_Y;

private:
    float m_fov;

protected:
    Axis m_axis;
    glm::vec2 m_lastMousePosition;

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
