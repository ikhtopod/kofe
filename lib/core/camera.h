#ifndef CAMERA_H
#define CAMERA_H

#include "icanbeeverywhere.h"
#include "icanbematrix.h"


class Camera :
        public ICanBeEverywhere,
        public ICanBeMatrix
{
public:
    virtual ~Camera() = default;
};

#endif // CAMERA_H
