#ifndef MESH_H
#define MESH_H

#include "iprocess.h"


class Mesh : public IProcess {
public:
    Mesh();
    ~Mesh();

public: /* IProcess */
    void Processing() override;
};

#endif // MESH_H
