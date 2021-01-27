#ifndef CAMERA_H
#define CAMERA_H

#include "icanbeeverywhere.h"
#include "icanbematrix.h"
#include "inputobserver.h"


class Camera :
        public ICanBeEverywhere,
        public ICanBeMatrix,
        public IInputObserver
{
public:
    Camera(const Camera&) = delete;
    Camera(Camera&&) noexcept = delete;
    Camera& operator=(const Camera&) = delete;
    Camera& operator=(Camera&&) noexcept = delete;

public:
    Camera();
    virtual ~Camera();
};

#endif // CAMERA_H
