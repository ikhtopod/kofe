#ifndef MATERIAL_H
#define MATERIAL_H

#include "iprocess.h"


class Material : public IProcess {
public:
    Material();
    ~Material();

public: /* IProcess */
    void Processing() override;
};

#endif // MATERIAL_H
