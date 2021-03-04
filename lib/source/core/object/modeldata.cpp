#include "object/modeldata.h"

#include "app_exceptions.h"
#include "everywhere.h"
#include "misc/vertex.h"
#include "texture/textureparams.h"
#include "material/phongmaterial.h"
#include "material/texturematerial.h"
#include "mesh/mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include <cstddef>
#include <string>
#include <regex>
#include <algorithm>
#include <iterator>


namespace {

namespace fs = std::filesystem;
namespace rx_const = std::regex_constants;

static struct ModelTempPaths {
    fs::path filepath {};
    fs::path textureDirectory {};

    void Reset() {
        filepath.clear();
        textureDirectory.clear();
    }
} sg_modelTempPath;

void CheckCorrectModelPath(fs::path path) {
    path = fs::canonical(path);

    if (!fs::exists(path)) {
        throw ModelDataException { "File \"" + path.string() + "\" isn't exists." };
    }

    if (fs::is_directory(path)) {
        throw ModelDataException { "File \"" + path.string() + "\" is directory." };
    }

    if (fs::is_socket(path)) {
        throw ModelDataException { "File \"" + path.string() + "\" is socket." };
    }

    if (fs::is_empty(path)) {
        throw ModelDataException { "File \"" + path.string() + "\" is empty." };
    }
}

glm::vec2 ToVec2(const aiVector3D& vec3d) {
    return { vec3d.x, vec3d.y };
}

glm::vec3 ToVec3(const aiVector3D& vec3d) {
    return { vec3d.x, vec3d.y, vec3d.z };
}

void InitVertices(aiMesh* mesh, std::vector<Vertex>& result) {
    result.resize(mesh->mNumVertices);

    for (size_t i = 0; i < mesh->mNumVertices; ++i) {
        result[i].position = ToVec3(mesh->mVertices[i]);

        if (mesh->HasNormals()) {
            result[i].normal = ToVec3(mesh->mNormals[i]);
        }

        if (mesh->HasTextureCoords(0)) {
            result[i].texture = ToVec2(mesh->mTextureCoords[0][i]);
        }
    }
}

void InitIndices(aiMesh* mesh, std::vector<GLuint>& result) {
    for (size_t i = 0; i < mesh->mNumFaces; ++i) {
        aiFace face = mesh->mFaces[i];

        for (size_t j = 0; j < face.mNumIndices; ++j) {
            result.push_back(face.mIndices[j]);
        }
    }
}

bool HasNoOneTextures(aiMaterial* material) {
    return !(material->GetTextureCount(aiTextureType_DIFFUSE) ||
             material->GetTextureCount(aiTextureType_SPECULAR) ||
             material->GetTextureCount(aiTextureType_EMISSIVE));
}

fs::path GetTexturePath(aiMaterial* material, aiTextureType type, size_t idx = 0) {
    fs::path texturePath =
        Everywhere::Instance().Get<TextureStorage>().GetDefaultTexturePath();

    if (material->GetTextureCount(type)) {
        aiString stringPath {};
        material->GetTexture(type, idx, &stringPath);
        texturePath = stringPath.C_Str();
    }

    return texturePath;
}

void CreateDefaultDummyMaterial() {
    Everywhere::Instance().Get<MaterialStorage>().GetMaterials().Add(
        std::make_shared<PhongMaterial>());
}

void CreateTextureMaterial(const fs::path& deffusePath,
                           const fs::path& specularPath,
                           const fs::path& emissionPath) {
    TextureParams diffuseTextureData { deffusePath, GL_TEXTURE0 };

    TextureParams specularTextureData { specularPath,
                                        diffuseTextureData.GetUnit() + 1 };

    TextureParams emissionTextureData { emissionPath,
                                        diffuseTextureData.GetUnit() + 2 };

    auto textureMaterial =
        std::make_shared<TextureMaterial>(diffuseTextureData,
                                          specularTextureData,
                                          emissionTextureData);

    Everywhere::Instance().Get<MaterialStorage>().GetMaterials().Add(textureMaterial);
}

bool IsSomeTextureFilename(const fs::path& stem, const fs::path& modelFilename, const std::string& postfix) {
    std::regex pattern { "^t_+" + modelFilename.string() + "_+" + postfix + "$",
                         rx_const::icase };
    return std::regex_search(stem.string(), pattern);
}

bool IsDiffuseTextureFilename(const fs::path& stem, const fs::path& modelFilename) {
    return IsSomeTextureFilename(stem, modelFilename, R"re(dif+use)re");
}

bool IsSpecularTextureFilename(const fs::path& stem, const fs::path& modelFilename) {
    return IsSomeTextureFilename(stem, modelFilename, R"re(specular)re");
}

bool IsEmissionTextureFilename(const fs::path& stem, const fs::path& modelFilename) {
    return IsSomeTextureFilename(stem, modelFilename, R"re(emis+i(?:(?:on)|(?:ve)))re");
}

bool CreateTextureMaterialByFilename(fs::path dirPath) {
    dirPath = fs::canonical(dirPath);

    fs::path deffusePath { Everywhere::Instance().Get<TextureStorage>().GetDefaultTexturePath() };
    fs::path specularPath { Everywhere::Instance().Get<TextureStorage>().GetDefaultTexturePath() };
    fs::path emissionPath { Everywhere::Instance().Get<TextureStorage>().GetDefaultTexturePath() };
    fs::path modelFilename { sg_modelTempPath.filepath.stem() };

    if (fs::exists(dirPath) && fs::is_directory(dirPath)) {
        bool wasFound = false;

        for (auto& entry : fs::directory_iterator(dirPath)) {
            if (!entry.is_regular_file()) continue;
            if (fs::canonical(entry.path()) == sg_modelTempPath.filepath) continue;

            if (IsDiffuseTextureFilename(entry.path().stem(), modelFilename)) {
                deffusePath = entry.path();
                wasFound = true;
            } else if (IsSpecularTextureFilename(entry.path().stem(), modelFilename)) {
                specularPath = entry.path();
                wasFound = true;
            } else if (IsEmissionTextureFilename(entry.path().stem(), modelFilename)) {
                emissionPath = entry.path();
                wasFound = true;
            }
        }

        if (wasFound) {
            CreateTextureMaterial(deffusePath, specularPath, emissionPath);
            return true;
        }
    }

    return false;
}

bool CreateTextureMaterialByDefaultFilenames() {
    if (CreateTextureMaterialByFilename(sg_modelTempPath.textureDirectory)) {
        return true;
    }

    fs::path currentDirectory = sg_modelTempPath.filepath.parent_path();
    if (currentDirectory != sg_modelTempPath.textureDirectory) {
        if (CreateTextureMaterialByFilename(currentDirectory)) {
            return true;
        }
    }

    std::regex pattern { R"re(^textures?$)re", rx_const::icase };
    for (auto& entry : fs::directory_iterator(currentDirectory)) {
        if (!entry.is_directory()) continue;

        if (std::regex_match(entry.path().stem().string(), pattern)) {
            if (CreateTextureMaterialByFilename(entry.path())) {
                return true;
            }
        }
    }

    return false;
}

void CreateTextureMaterialByAssimpMaterial(aiMaterial* material) {
    CreateTextureMaterial(
        sg_modelTempPath.filepath.parent_path() / GetTexturePath(material, aiTextureType_DIFFUSE),
        sg_modelTempPath.filepath.parent_path() / GetTexturePath(material, aiTextureType_SPECULAR),
        sg_modelTempPath.filepath.parent_path() / GetTexturePath(material, aiTextureType_EMISSIVE));
}

size_t GetMaterialId(aiMesh* mesh, const aiScene* scene) {
    if (!mesh || !scene) return 0;

    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    if (!material) {
        if (!CreateTextureMaterialByDefaultFilenames()) {
            CreateDefaultDummyMaterial();
        }
    } else {
        if (HasNoOneTextures(material)) {
            if (!CreateTextureMaterialByDefaultFilenames()) {
                CreateDefaultDummyMaterial();
            }
        } else {
            size_t size = Everywhere::Instance().Get<MaterialStorage>().GetMaterials().Size();

            CreateTextureMaterialByAssimpMaterial(material);

            if (size == Everywhere::Instance().Get<MaterialStorage>().GetMaterials().Size()) {
                if (!CreateTextureMaterialByDefaultFilenames()) {
                    CreateDefaultDummyMaterial();
                }
            }
        }
    }

    return Everywhere::Instance().Get<MaterialStorage>().GetLastMaterialID();
}

void FindLODFiles(const fs::path& mainFile, std::vector<fs::path>& lodPaths) {
    const fs::path onlyFilename = mainFile.stem();
    const fs::path currentDirectory = mainFile.parent_path();

    std::regex pattern { "^" + onlyFilename.string() + "[\\._-]+lod[\\._-]?\\d+$",
                         rx_const::icase };

    for (auto& entry : fs::directory_iterator(currentDirectory)) {
        if (!entry.is_regular_file()) continue;
        if (fs::canonical(entry.path()) == fs::canonical(mainFile)) continue;
        if (!entry.path().has_extension()) continue;
        if (entry.path().extension() != mainFile.extension()) continue;

        if (std::regex_match(entry.path().stem().string(), pattern)) {
            lodPaths.push_back(fs::canonical(entry.path()));
        }
    }
}

void SortLodsByPostfixNumber(std::vector<fs::path>& lodPaths) {
    auto pred = [](const fs::path& a, const fs::path& b) -> bool {
        std::regex pattern { "^.+lod[\\._-]?0*(\\d+)$", rx_const::icase };
        std::smatch mA {}, mB {};
        const std::string strA { a.stem().string() };
        const std::string strB { b.stem().string() };

        if (!std::regex_match(strA, mA, pattern)) {
            throw ModelDataException {
                "Wrong match in sort function. Incorrect lod name " + a.string()
            };
        }

        if (!std::regex_match(strB, mB, pattern)) {
            throw ModelDataException {
                "Wrong match in sort function. Incorrect lod name " + b.string()
            };
        }

        return std::stoi(mA.str(1)) < std::stoi(mB.str(1));
    };

    std::sort(std::begin(lodPaths), std::end(lodPaths), pred);
}

} // namespace


void swap(ModelData& lhs, ModelData& rhs) {
    if (&lhs == &rhs) return;

    using std::swap;

    swap(static_cast<Object>(lhs), static_cast<Object>(rhs));
    swap(lhs.m_lods, rhs.m_lods);
    swap(lhs.m_distanceStep, rhs.m_distanceStep);
}


void ModelData::ProcessSceneMesh(aiMesh* mesh, const aiScene* scene) {
    if (!mesh) return;

    std::vector<Vertex> vertices {};
    std::vector<GLuint> indices {};

    InitVertices(mesh, vertices);
    InitIndices(mesh, indices);

    auto meshOfModel = std::make_shared<Mesh>(std::move(vertices), std::move(indices));
    meshOfModel->SetMaterialId(GetMaterialId(mesh, scene));

    m_lods.Back()->Children().Add(meshOfModel);
}

void ModelData::ProcessSceneNode(aiNode* node, const aiScene* scene) {
    if (!node) return;

    for (size_t i = 0; i < node->mNumMeshes; ++i) {
        size_t meshId = node->mMeshes[i];

        if (scene) {
            ProcessSceneMesh(scene->mMeshes[meshId], scene);
        }
    }

    for (size_t i = 0; i < node->mNumChildren; ++i) {
        ProcessSceneNode(node->mChildren[i], scene);
    }
}

void ModelData::InitMeshLOD(const std::vector<std::filesystem::path>& lodPaths) {
    for (const fs::path& lodPath : lodPaths) {
        Assimp::Importer importer {};

        unsigned int postProcessParams = aiProcess_JoinIdenticalVertices |
                                         aiProcess_Triangulate;

        const aiScene* scene = importer.ReadFile(lodPath.string(), postProcessParams);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            throw ModelDataException {
                "Can't import scene for file \"" + lodPath.string() + "\"\n" +
                "Assimp message: " + importer.GetErrorString()
            };
        }

        m_lods.Add(std::make_shared<Object>());
        ProcessSceneNode(scene->mRootNode, scene);
    }
}

void ModelData::ImportModelData() {
    CheckCorrectModelPath(sg_modelTempPath.filepath);

    std::vector<fs::path> lodPaths {};
    FindLODFiles(sg_modelTempPath.filepath, lodPaths);

    if (lodPaths.size() > 1) {
        SortLodsByPostfixNumber(lodPaths);
    }

    lodPaths.insert(lodPaths.begin(), sg_modelTempPath.filepath);
    InitMeshLOD(lodPaths);
}

ModelData::ModelData(const fs::path& path) :
    ModelData { path, path.parent_path() } {}

ModelData::ModelData(const fs::path& path,
                     const fs::path& textureDirectory) :
    m_lods {},
    m_distanceStep {} {

    sg_modelTempPath = {
        fs::canonical(path),
        fs::canonical(textureDirectory)
    };

    ImportModelData();
    UpdateDistanceStep();

    sg_modelTempPath.Reset();
}

ModelData::~ModelData() {
    m_lods.Clear();
}

void ModelData::UpdateDistanceStep() {
    m_distanceStep =
        Everywhere::Instance().Get<Projection>().GetDepthFar() / m_lods.Size();
}

float ModelData::GetDistanceToCamera() const {
    return glm::distance(
        Everywhere::Instance().Get<Camera>().GetTransform().GetPosition(),
        GetGlobalTransform().GetPosition());
}

size_t ModelData::GetCurrentLodId() const {
    return static_cast<size_t>(GetDistanceToCamera() / m_distanceStep);
}

CollectionOf<Object>& ModelData::GetLODs() {
    return m_lods;
}

const CollectionOf<Object>& ModelData::GetLODs() const {
    return m_lods;
}

void ModelData::Processing() {
    if (!m_lods.IsEmpty()) {
        size_t lodId = GetCurrentLodId();

        if (lodId < m_lods.Size()) {
            m_lods.At(lodId)->SetParentTransform(GetParentTransform());
            m_lods.At(lodId)->SetTransform(GetTransform());
            m_lods.At(lodId)->Processing();
        }
    }

    Object::Processing(); // update children
}
