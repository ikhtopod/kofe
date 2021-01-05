#ifndef SPACE_H
#define SPACE_H

#include "iprocess.h"
#include "scene.h"

#include <glm/glm.hpp>

#include <vector>


class Space final : public IProcess {
private:
    const glm::mat4 MODEL;

    std::vector<Scene*> m_scenes;

public:
    Space();
    ~Space();

public: /* IProcess */
    void Processing() override;
};

#endif // SPACE_H
