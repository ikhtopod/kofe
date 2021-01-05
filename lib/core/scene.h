#ifndef SCENE_H
#define SCENE_H

#include "iprocess.h"

#include <cstddef>
#include <vector>
#include <memory>


class Scene : public IProcess {
public:
    Scene();
    ~Scene();

public: /* IProcess */
    void Processing() override;
};

#endif // SCENE_H
