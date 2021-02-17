#ifndef ICANBEMATRIX_H
#define ICANBEMATRIX_H

#include <glm/matrix.hpp>


class ICanBeMatrix {
public:
    virtual ~ICanBeMatrix() = default;

public:
    virtual glm::mat4 ToMatrix() const = 0;
};

#endif // ICANBEMATRIX_H
