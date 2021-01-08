#ifndef SPACE_H
#define SPACE_H

#include "iprocess.h"
#include "collectionof.h"
#include "scene.h"

#include <glm/glm.hpp>


class Space final : public IProcess {
    static const glm::mat4 MODEL;

private:
    CollectionOf<Scene> m_scenes;

public:
    Space();
    ~Space();

public:
    CollectionOf<Scene>& GetScenes();
    const CollectionOf<Scene>& GetScenes() const;

public: /* IProcess */
    void Processing() override;
};

#endif // SPACE_H
