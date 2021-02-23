#ifndef MODEL_H
#define MODEL_H

#include "object.h"
#include "mesh/mesh.h"

#include <assimp/scene.h>

#include <filesystem>


class Model :
    public Object {
public:
    Model() = delete;
    Model(const Model&) = delete;
    Model(Model&&) noexcept = delete;
    Model& operator=(const Model&) = delete;
    Model& operator=(Model&&) noexcept = delete;

public:
    virtual ~Model() = default;

    explicit Model(const std::filesystem::path& path);
    explicit Model(const std::filesystem::path& path,
                   const std::filesystem::path& textureDirectory);

private:
    void ProcessSceneNode(aiNode* node, const aiScene* scene);
    void ProcessSceneMesh(aiMesh* mesh, const aiScene* scene);
    void ImportModel();
};

#endif // MODEL_H
