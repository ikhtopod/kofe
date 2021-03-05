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

bool ModelStorage::HasModel(std::filesystem::path path) const {
    path = std::filesystem::canonical(path);
    return static_cast<bool>(m_models.count(path.string()));
}

void ModelStorage::CreateModelData(std::filesystem::path path) const {
    if (path.empty()) {
        throw ModelStorageException { "An empty file path was received." };
    }

    if (!m_models.count(path.string())) {
        m_models.insert({ path.string(), std::make_shared<ModelData>(path, path.parent_path()) });
    }
}

void ModelStorage::CreateModelData(std::filesystem::path path,
                                   std::filesystem::path textureDirectory) const {
    if (path.empty()) {
        throw ModelStorageException { "An empty file path was received." };
    }

    if (!m_models.count(path.string())) {
        m_models.insert({ path.string(), std::make_shared<ModelData>(path, textureDirectory) });
    }
}

const ModelStorage::ValueType ModelStorage::Get(std::filesystem::path path) const {
    CreateModelData(path, path.parent_path());
    return m_models.at(path.string());
}

const ModelStorage::ValueType
    ModelStorage::Get(std::filesystem::path path, std::filesystem::path textureDirectory) const {
    CreateModelData(path, textureDirectory);
    return m_models.at(path.string());
}
