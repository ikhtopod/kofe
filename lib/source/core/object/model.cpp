#include "object/model.h"

#include "app_exceptions.h"
#include "everywhere.h"
#include "misc/vertex.h"
#include "material/phongmaterial.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

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

void Model::ProcessSceneMesh(aiMesh* mesh, [[maybe_unused]] const aiScene* scene) {
    std::vector<Vertex> vertices {};
    std::vector<GLuint> indices {};

    InitVertices(mesh, vertices);
    InitIndices(mesh, indices);

    //size_t materialIndex = mesh->mMaterialIndex;
    auto tempPhongMaterial = std::make_shared<PhongMaterial>();
    tempPhongMaterial->SetAmbientAndDiffuse(Color { 0.8f, 0.8f, 0.8f, 1.0f });

    Everywhere::Instance().Get<MaterialStorage>().GetMaterials().Add(tempPhongMaterial);
    auto meshOfModel = std::make_shared<Mesh>(vertices, indices);
    size_t materialId =
        Everywhere::Instance().Get<MaterialStorage>().GetMaterials().Size() - 1;
    meshOfModel->SetMaterialId(materialId);

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
