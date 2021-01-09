#ifndef SHADER_H
#define SHADER_H

#include "iprocess.h"


class Shader : public IProcess {
public:
    Shader();
    ~Shader();

public: /* IProcess */
    void Processing() override;
};

#endif // SHADER_H
