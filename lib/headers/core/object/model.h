#ifndef MODEL_H
#define MODEL_H

#include "object.h"
#include "mesh/mesh.h"
#include "misc/collectionof.h"

#include <assimp/scene.h>

#include <filesystem>
#include <vector>


class Model : public Object {
private:
    CollectionOf<Object> m_lods;
    float m_distanceStep;

public:
    Model() = delete;
    Model(const Model&) = delete;
    Model(Model&&) noexcept = delete;
    Model& operator=(const Model&) = delete;
    Model& operator=(Model&&) noexcept = delete;

public:
    explicit Model(const std::filesystem::path& path);
    explicit Model(const std::filesystem::path& path,
                   const std::filesystem::path& textureDirectory);
    virtual ~Model();

private:
    void UpdateDistanceStep();
    float GetDistanceToCamera() const;
    size_t GetCurrentLodId() const;

private:
    void ProcessSceneNode(aiNode* node, const aiScene* scene);
    void ProcessSceneMesh(aiMesh* mesh, const aiScene* scene);
    void InitMeshLOD(const std::vector<std::filesystem::path>& lodPaths);

    void ImportModel();

public:
    CollectionOf<Object>& GetLODs();
    const CollectionOf<Object>& GetLODs() const;

public: /* IProcess */
    void Processing() override;
};

#endif // MODEL_H
