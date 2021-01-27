#ifndef CAMERA_H
#define CAMERA_H

#include "icanbeeverywhere.h"
#include "icanbematrix.h"
#include "inputobserver.h"
#include "localtransformation.h"


class Camera :
        public ICanBeEverywhere,
        public ICanBeMatrix,
        public IInputObserver,
        public LocalTransformation
{
private:
    static const float DEFAULT_FOV;

private:
    float m_fov;

public:
    Camera(const Camera&) = delete;
    Camera(Camera&&) noexcept = delete;
    Camera& operator=(const Camera&) = delete;
    Camera& operator=(Camera&&) noexcept = delete;

public:
    Camera();
    virtual ~Camera();

public:
    float GetFoV() const;
};

#endif // CAMERA_H
