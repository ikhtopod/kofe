#ifndef OBJECT_H
#define OBJECT_H

#include "interface/iprocess.h"
#include "transform/transformable.h"
#include "misc/collectionof.h"


class Object :
    public IProcess,
    public Transformable {
protected:
    CollectionOf<Object> m_children;

public:
    Object();
    virtual ~Object();

public:
    CollectionOf<Object>& Children();
    const CollectionOf<Object>& Children() const;

public: /* IProcess */
    void Processing() override;
};

#endif // OBJECT_H
