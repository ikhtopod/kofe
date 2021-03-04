#ifndef MODELSTORAGE_H
#define MODELSTORAGE_H

#include "object/modeldata.h"
#include "interface/icanbeeverywhere.h"

#include <unordered_map>
#include <filesystem>
#include <string>
#include <vector>
#include <memory>


class ModelStorage final : public ICanBeEverywhere {
private:
    using StoredType = ModelData;
    using KeyType = std::string;
    using ValueType = std::shared_ptr<StoredType>;

private:
    mutable std::unordered_map<KeyType, ValueType> m_models {};

public:
    ModelStorage(const ModelStorage&) = delete;
    ModelStorage(ModelStorage&&) noexcept = delete;
    ModelStorage& operator=(const ModelStorage&) = delete;
    ModelStorage& operator=(ModelStorage&&) noexcept = delete;

public:
    ModelStorage();
    ~ModelStorage();

public:
    void CreateModelData(std::filesystem::path path) const;

    void CreateModelData(std::filesystem::path path,
                         std::filesystem::path textureDirectory) const;

    const ValueType Get(std::filesystem::path path) const;

    const ValueType Get(std::filesystem::path path,
                        std::filesystem::path textureDirectory) const;
};

#endif // MODELSTORAGE_H
