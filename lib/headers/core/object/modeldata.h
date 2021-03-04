#ifndef MODELDATA_H
#define MODELDATA_H

#include "object.h"
#include "misc/collectionof.h"

#include <assimp/scene.h>

#include <filesystem>
#include <vector>


class ModelData : public Object {
private:
    CollectionOf<Object> m_lods;
    float m_distanceStep;

public:
    friend void swap(ModelData&, ModelData&);

public:
    ModelData() = delete;
    ModelData(const ModelData&) = delete;
    ModelData(ModelData&&) noexcept = delete;
    ModelData& operator=(const ModelData&) = delete;
    ModelData& operator=(ModelData&&) noexcept = delete;

public:
    explicit ModelData(const std::filesystem::path& path);
    explicit ModelData(const std::filesystem::path& path,
                       const std::filesystem::path& textureDirectory);
    virtual ~ModelData();

private:
    void UpdateDistanceStep();
    float GetDistanceToCamera() const;
    size_t GetCurrentLodId() const;

private:
    void ProcessSceneNode(aiNode* node, const aiScene* scene);
    void ProcessSceneMesh(aiMesh* mesh, const aiScene* scene);
    void InitMeshLOD(const std::vector<std::filesystem::path>& lodPaths);

    void ImportModelData();

public:
    CollectionOf<Object>& GetLODs();
    const CollectionOf<Object>& GetLODs() const;

public: /* IProcess */
    void Processing() override;
};


void swap(ModelData& lhs, ModelData& rhs);

#endif // MODELDATA_H
