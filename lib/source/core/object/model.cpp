#include "object/model.h"

#include "app_exceptions.h"
#include "everywhere.h"
#include "misc/vertex.h"
#include "texture/texturedata.h"
#include "material/phongmaterial.h"
#include "material/texturematerial.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include <cstddef>
#include <vector>


namespace {

void CheckCorrectModelPath(std::filesystem::path path) {
    path = std::filesystem::canonical(path);

    if (!std::filesystem::exists(path)) {
        throw ModelException { "File \"" + path.string() + "\" isn't exists." };
    }

    if (std::filesystem::is_directory(path)) {
        throw ModelException { "File \"" + path.string() + "\" is directory." };
    }

    if (std::filesystem::is_socket(path)) {
        throw ModelException { "File \"" + path.string() + "\" is socket." };
    }

    if (std::filesystem::is_empty(path)) {
        throw ModelException { "File \"" + path.string() + "\" is empty." };
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

std::filesystem::path GetTexturePath(aiMaterial* material, aiTextureType type, size_t idx = 0) {
    std::filesystem::path texturePath =
        Everywhere::Instance().Get<TextureStorage>().GetDefaultTexturePath();

    if (material->GetTextureCount(type)) {
        aiString stringPath {};
        material->GetTexture(type, idx, &stringPath);
        texturePath = stringPath.C_Str();
    }

    return texturePath;
}

size_t GetMaterialId(aiMesh* mesh, const aiScene* scene) {
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    if (!material || HasNoOneTextures(material)) {
        Everywhere::Instance().Get<MaterialStorage>().GetMaterials().Add(
            std::make_shared<PhongMaterial>());
    } else {
        TextureData diffuseTextureData {
            GetTexturePath(material, aiTextureType_DIFFUSE),
            GL_TEXTURE0
        };

        TextureData specularTextureData {
            GetTexturePath(material, aiTextureType_SPECULAR),
            diffuseTextureData.GetUnit() + 1
        };

        TextureData emissionTextureData {
            GetTexturePath(material, aiTextureType_EMISSIVE),
            diffuseTextureData.GetUnit() + 2
        };

        auto textureMaterial =
            std::make_shared<TextureMaterial>(diffuseTextureData,
                                              specularTextureData,
                                              emissionTextureData);
        Everywhere::Instance().Get<MaterialStorage>().GetMaterials().Add(textureMaterial);
    }

    return Everywhere::Instance().Get<MaterialStorage>().GetLastMaterialID();
}

} // namespace


void Model::ProcessSceneNode(aiNode* node, const aiScene* scene) {
    for (size_t i = 0; i < node->mNumMeshes; ++i) {
        size_t meshId = node->mMeshes[i];
        ProcessSceneMesh(scene->mMeshes[meshId], scene);
    }

    for (size_t i = 0; i < node->mNumChildren; ++i) {
        ProcessSceneNode(node->mChildren[i], scene);
    }
}

void Model::ProcessSceneMesh(aiMesh* mesh, const aiScene* scene) {
    std::vector<Vertex> vertices {};
    std::vector<GLuint> indices {};

    InitVertices(mesh, vertices);
    InitIndices(mesh, indices);

    auto meshOfModel = std::make_shared<Mesh>(std::move(vertices), std::move(indices));
    meshOfModel->SetMaterialId(GetMaterialId(mesh, scene));

    Children().Add(meshOfModel);
}

void Model::ImportModel(std::filesystem::path path) {
    path = std::filesystem::canonical(path);

    CheckCorrectModelPath(path);

    Assimp::Importer importer {};

    // More postprocess:
    // aiProcess_FindInstances
    // aiProcess_FlipWindingOrder
    // aiProcess_FlipUVs

    unsigned int postProcessParams = aiProcess_JoinIdenticalVertices |
                                     aiProcess_Triangulate;

    const aiScene* scene = importer.ReadFile(path.string(), postProcessParams);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        throw ModelException {
            "Can't import scene for file \"" + path.string() + "\"\n" +
            "Assimp message: " + importer.GetErrorString()
        };
    }

    ProcessSceneNode(scene->mRootNode, scene);
}

Model::Model(const std::filesystem::path& path) {
    ImportModel(path);
}
