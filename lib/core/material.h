#ifndef MATERIAL_H
#define MATERIAL_H

#include "iprocess.h"
#include "collectionof.h"


class Material : public IProcess {
private:


public:
    Material();
    ~Material();

public: /* IProcess */
    void Processing() override;
};

#endif // MATERIAL_H
