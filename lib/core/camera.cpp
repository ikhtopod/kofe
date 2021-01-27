#include "camera.h"

#include "everywhere.h"


Camera::Camera() {
    Everywhere::Instance().Get<Input>().Attach(this);
}

Camera::~Camera() {
    Everywhere::Instance().Get<Input>().Detach(this);
}
