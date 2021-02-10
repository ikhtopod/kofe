#include "light.h"


Light::Light() :
    Object {},
    m_color {} {}

Color Light::GetColor() const {
    return m_color;
}

void Light::SetColor(const Color& color) {
    m_color = color;
}

void Light::Processing() {
    Object::Processing();
}
