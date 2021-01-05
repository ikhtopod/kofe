#ifndef SPACE_H
#define SPACE_H

#include "iprocess.h"
#include "scene.h"

#include <glm/glm.hpp>

#include <cstddef>
#include <vector>
#include <memory>


class Space final : public IProcess {
    using SceneSPtr = std::shared_ptr<Scene>;

private:
    const glm::mat4 MODEL;

    std::vector<SceneSPtr> m_scenes;

public:
    Space();
    ~Space();

public: /* Scene operations */
    void AddScene(SceneSPtr& scene);
    void DeleteScene(size_t index);
    void ClearScenes();

public: /* IProcess */
    void Processing() override;
};

#endif // SPACE_H
