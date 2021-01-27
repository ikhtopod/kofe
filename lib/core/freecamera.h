#ifndef FREECAMERA_H
#define FREECAMERA_H

#include "camera.h"


class FreeCamera : public Camera {
public:
    FreeCamera();
    virtual ~FreeCamera() = default;

public: /* ICanBeMatrix */
    glm::mat4 ToMatrix() const override;

public: /* IInputObserver */
    void UpdateInput() override;
};

#endif // FREECAMERA_H
