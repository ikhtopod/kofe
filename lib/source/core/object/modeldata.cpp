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


} // namespace


void swap(ModelData& lhs, ModelData& rhs) {
    if (&lhs == &rhs) return;

    using std::swap;

    swap(static_cast<Object>(lhs), static_cast<Object>(rhs));
}


void ModelData::ProcessSceneMesh(aiMesh* mesh, const aiScene* scene) {
    if (!mesh) return;

    std::vector<Vertex> vertices {};
    std::vector<GLuint> indices {};

    InitVertices(mesh, vertices);
    InitIndices(mesh, indices);

    auto meshOfModel = std::make_shared<Mesh>(std::move(vertices), std::move(indices));
    meshOfModel->SetMaterialId(GetMaterialId(mesh, scene));

    Children().Add(meshOfModel);
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

void ModelData::ImportModelData() {
    CheckCorrectModelPath(sg_modelTempPath.filepath);

    Assimp::Importer importer {};

    unsigned int postProcessParams = aiProcess_JoinIdenticalVertices |
                                     aiProcess_Triangulate;

    const aiScene* scene =
        importer.ReadFile(sg_modelTempPath.filepath.string(), postProcessParams);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        throw ModelDataException {
            "Can't import scene for file \"" + sg_modelTempPath.filepath.string() + "\"\n" +
            "Assimp message: " + importer.GetErrorString()
        };
    }

    ProcessSceneNode(scene->mRootNode, scene);
}

ModelData::ModelData(const fs::path& path) :
    ModelData { path, path.parent_path() } {}

ModelData::ModelData(const fs::path& path,
                     const fs::path& textureDirectory) :
    Object {} {

    sg_modelTempPath = {
        fs::canonical(path),
        fs::canonical(textureDirectory)
    };

    ImportModelData();

    sg_modelTempPath.Reset();
}
