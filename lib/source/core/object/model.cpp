#include "object/model.h"

#include "everywhere.h"

#include <utility>


void swap(Model& lhs, Model& rhs) {
    if (&lhs == &rhs) return;

    using std::swap;

    swap(static_cast<Object>(lhs), static_cast<Object>(rhs));
    swap(lhs.m_pathId, rhs.m_pathId);
}


Model::Model(const Model& other) :
    Object { other },
    m_pathId { other.m_pathId } {}

Model::Model(Model&& other) noexcept :
    Object { std::move(other) },
    m_pathId { other.m_pathId } {}

Model& Model::operator=(const Model& other) {
    if (this != &other) {
        Object::operator=(other);
        m_pathId = other.m_pathId;
    }

    return *this;
}

Model& Model::operator=(Model&& other) noexcept {
    if (this != &other) {
        Object::operator=(std::move(other));
        m_pathId = std::move(other.m_pathId);
    }

    return *this;
}

Model::Model(const std::filesystem::path& path) :
    Model { std::filesystem::canonical(path),
            std::filesystem::canonical(path).parent_path() } {}

Model::Model(const std::filesystem::path& path,
             const std::filesystem::path& textureDirectory) :
    m_pathId { std::filesystem::canonical(path) } {

    Everywhere::Instance().Get<ModelStorage>().CreateModelData(
        m_pathId, std::filesystem::canonical(textureDirectory));
}

void Model::Processing() {
    auto modelData = Everywhere::Instance().Get<ModelStorage>().Get(m_pathId);

    if (modelData) {
        modelData->SetParentTransform(GetParentTransform());
        modelData->SetTransform(GetTransform());

        modelData->Processing();
    }

    Object::Processing(); // update children
}
