#ifndef OBJECT_H
#define OBJECT_H

#include "iprocess.h"


class Object : public IProcess {
public:
    Object();
    ~Object();

public: /* IProcess */
    void Processing() override;
};

#endif // OBJECT_H
