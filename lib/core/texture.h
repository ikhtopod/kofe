#ifndef TEXTURE_H
#define TEXTURE_H

#include "iprocess.h"


class Texture : public IProcess {
public:
    Texture();
    ~Texture();

public: /* IProcess */
    void Processing() override;
};

#endif // TEXTURE_H
