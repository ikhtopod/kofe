#ifndef TRANSFORMABLE_H
#define TRANSFORMABLE_H

#include "localtransformation.h"
#include "parenttransformation.h"


class Transformable :
    public ParentTransformation,
    public LocalTransformation {
public:
    Transformable();
    Transformable(const Transformable& other);
    Transformable(Transformable&& other) noexcept;
    Transformable& operator=(const Transformable& other);
    Transformable& operator=(Transformable&& other) noexcept;
    virtual ~Transformable() = default;

public:
    explicit Transformable(const Transform& parent, const Transform& local);
    explicit Transformable(const ParentTransformation& parent, const LocalTransformation& local);

public:
    virtual Transform GetGlobalTransform();
    virtual const Transform GetGlobalTransform() const;

public:
    friend void swap(Transformable&, Transformable&);
};


void swap(Transformable& lhs, Transformable& rhs);

#endif // TRANSFORMABLE_H
