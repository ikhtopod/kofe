#ifndef MODELDATA_H
#define MODELDATA_H

#include "object.h"
#include "misc/collectionof.h"

#include <assimp/scene.h>

#include <filesystem>
#include <vector>


class ModelData : public Object {
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
    virtual ~ModelData() = default;

private:
    void ProcessSceneNode(aiNode* node, const aiScene* scene);
    void ProcessSceneMesh(aiMesh* mesh, const aiScene* scene);
    void ImportModelData();
};


void swap(ModelData& lhs, ModelData& rhs);

#endif // MODELDATA_H
