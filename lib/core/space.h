#ifndef SPACE_H
#define SPACE_H

#include "iprocess.h"


class Space final : public IProcess {
public:
    Space();
    ~Space();

public: /* IProcess */
    void Processing() override;
};

#endif // SPACE_H
