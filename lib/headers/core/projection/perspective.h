#ifndef PERSPECTIVE_H
#define PERSPECTIVE_H

#include "projection.h"


class Perspective : public Projection {
public:
    Perspective(Perspective&& other) noexcept = delete;
    Perspective& operator=(Perspective&& other) noexcept = delete;

    Perspective() = default;
    Perspective(const Perspective& other) = default;
    Perspective& operator=(const Perspective& other) = default;
    virtual ~Perspective() = default;

public: /* ICanBeMatrix -> Projection */
    glm::mat4 ToMatrix() const override;
};

#endif // PERSPECTIVE_H
