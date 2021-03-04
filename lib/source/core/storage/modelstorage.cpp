#include "storage/modelstorage.h"

#include "app_exceptions.h"


ModelStorage::ModelStorage() :
    m_models {} {}

ModelStorage::~ModelStorage() {
    for (auto& [key, model] : m_models) {
        model.reset();
    }

    m_models.clear();
}

void ModelStorage::CreateModelData(std::filesystem::path path) const {
    path = std::filesystem::canonical(path);

    CreateModelData(path, path.parent_path());
}

void ModelStorage::CreateModelData(std::filesystem::path path,
                                   std::filesystem::path textureDirectory) const {
    if (path.empty()) {
        throw ModelStorageException { "An empty file path was received." };
    }

    path = std::filesystem::canonical(path);
    textureDirectory = std::filesystem::canonical(textureDirectory);

    if (!m_models.count(path.string())) {
        m_models.insert({ path.string(), std::make_shared<ModelData>(path, textureDirectory) });
    }
}

const ModelStorage::ValueType ModelStorage::Get(std::filesystem::path path) const {
    path = std::filesystem::canonical(path);

    return Get(path, path.parent_path());
}

const ModelStorage::ValueType
    ModelStorage::Get(std::filesystem::path path, std::filesystem::path textureDirectory) const {
    path = std::filesystem::canonical(path);
    textureDirectory = std::filesystem::canonical(textureDirectory);

    CreateModelData(path, textureDirectory);

    return m_models.at(path.string());
}
