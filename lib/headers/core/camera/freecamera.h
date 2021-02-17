#ifndef FREECAMERA_H
#define FREECAMERA_H

#include "camera.h"


class FreeCamera : public Camera {
public:
    FreeCamera();
    virtual ~FreeCamera() = default;

public: /* IInputObserver */
    void UpdateInput() override;
};

#endif // FREECAMERA_H
