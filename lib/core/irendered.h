#ifndef IRENDERED_H
#define IRENDERED_H

struct IRendered {
    virtual ~IRendered() = default;
    virtual void Rendering() = 0;
};

#endif // IRENDERED_H
