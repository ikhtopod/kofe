#ifndef OBJECT_H
#define OBJECT_H

#include "iprocess.h"
#include "transformable.h"
#include "collectionof.h"


class Object :
        public IProcess,
        public Transformable
{
protected:
    CollectionOf<Object> m_children;

public:
    Object();
    ~Object();

public:
    CollectionOf<Object>& Children();
    const CollectionOf<Object>& Children() const;

public: /* IProcess */
    void Processing() override;
};

#endif // OBJECT_H
