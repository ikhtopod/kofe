#ifndef MODELDATA_H
#define MODELDATA_H

#include "object.h"

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
};


class ModelDataImporter final {
private:
    std::filesystem::path m_filepath;
    std::filesystem::path m_textureDirectory;
    ModelData* m_modelData;

public:
    ModelDataImporter() = delete;
    ModelDataImporter(const ModelDataImporter&) = delete;
    ModelDataImporter(ModelDataImporter&&) noexcept = delete;
    ModelDataImporter& operator=(const ModelDataImporter&) = delete;
    ModelDataImporter& operator=(ModelDataImporter&&) noexcept = delete;

public:
    ModelDataImporter(std::filesystem::path filepath,
                      std::filesystem::path textureDirectory,
                      ModelData* modelData);
    ~ModelDataImporter() = default;

private:
    bool CreateTextureMaterialByFilename(const std::filesystem::path& textureDirectory) const;
    bool CreateTextureMaterialByDefaultFilenames() const;
    size_t GetMaterialId(aiMesh* mesh, const aiScene* scene) const;
    void CheckCorrectModelPath() const;
    void CreateTextureMaterialByAssimpMaterial(aiMaterial* material) const;

private:
    void ProcessSceneNode(aiNode* node, const aiScene* scene);
    void ProcessSceneMesh(aiMesh* mesh, const aiScene* scene);

public:
    void Import();
};


void swap(ModelData& lhs, ModelData& rhs);

#endif // MODELDATA_H
