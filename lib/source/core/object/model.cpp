#include "object/model.h"

#include "app_exceptions.h"
#include "everywhere.h"

#include <string>
#include <utility>
#include <regex>
#include <algorithm>


namespace {

namespace fs = std::filesystem;
namespace rx_const = std::regex_constants;

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
            throw ModelException {
                "Wrong match in sort function. Incorrect lod name " + a.string()
            };
        }

        if (!std::regex_match(strB, mB, pattern)) {
            throw ModelException {
                "Wrong match in sort function. Incorrect lod name " + b.string()
            };
        }

        return std::stoi(mA.str(1)) < std::stoi(mB.str(1));
    };

    std::sort(std::begin(lodPaths), std::end(lodPaths), pred);
}

} // namespace


void swap(Model& lhs, Model& rhs) {
    if (&lhs == &rhs) return;

    using std::swap;

    swap(static_cast<Object>(lhs), static_cast<Object>(rhs));
    swap(lhs.m_lods, rhs.m_lods);
    swap(lhs.m_distanceStep, rhs.m_distanceStep);
}


Model::Model(const Model& other) :
    Object { other },
    m_lods { other.m_lods },
    m_distanceStep { other.m_distanceStep } {}

Model::Model(Model&& other) noexcept :
    Object { std::move(other) },
    m_lods { std::move(other.m_lods) },
    m_distanceStep { std::move(other.m_distanceStep) } {}

Model& Model::operator=(const Model& other) {
    if (this != &other) {
        Object::operator=(other);
        m_lods = other.m_lods;
        m_distanceStep = other.m_distanceStep;
    }

    return *this;
}

Model& Model::operator=(Model&& other) noexcept {
    if (this != &other) {
        Object::operator=(std::move(other));
        m_lods = std::move(other.m_lods);
        m_distanceStep = std::move(other.m_distanceStep);
    }

    return *this;
}

Model::Model(const std::filesystem::path& path) :
    Model { std::filesystem::canonical(path),
            std::filesystem::canonical(path).parent_path() } {}

Model::Model(std::filesystem::path path,
             std::filesystem::path textureDirectory) :
    m_lods {},
    m_distanceStep {} {

    path = std::filesystem::canonical(path);
    textureDirectory = std::filesystem::canonical(textureDirectory);

    if (path.empty()) {
        throw ModelException { "An empty file path was received." };
    }

    UpdateLODs(path);

    for (auto& lodPath : m_lods) {
        if (!Everywhere::Instance().Get<ModelStorage>().HasModel(lodPath)) {
            Everywhere::Instance().Get<ModelStorage>().CreateModelData(
                lodPath, std::filesystem::canonical(textureDirectory));
        }
    }
}

Model::~Model() {
    m_lods.clear();
}

std::vector<std::filesystem::path>& Model::GetLODs() {
    return m_lods;
}

const std::vector<std::filesystem::path>& Model::GetLODs() const {
    return m_lods;
}

void Model::UpdateDistanceStep() {
    m_distanceStep =
        Everywhere::Instance().Get<Projection>().GetDepthFar() / m_lods.size();
}

void Model::UpdateLODs(const std::filesystem::path& path) {
    FindLODFiles(path, m_lods);

    if (m_lods.size() > 1) {
        SortLodsByPostfixNumber(m_lods);
    }

    m_lods.insert(m_lods.begin(), path);

    UpdateDistanceStep();
}

float Model::GetDistanceToCamera() const {
    return glm::distance(
        Everywhere::Instance().Get<Camera>().GetTransform().GetPosition(),
        GetGlobalTransform().GetPosition());
}

size_t Model::GetCurrentLodId() const {
    return static_cast<size_t>(GetDistanceToCamera() / m_distanceStep);
}

void Model::Processing() {
    size_t lodId = GetCurrentLodId();

    if (lodId < m_lods.size()) {
        auto modelData =
            Everywhere::Instance().Get<ModelStorage>().Get(m_lods.at(lodId));

        if (modelData) {
            modelData->SetParentTransform(GetParentTransform());
            modelData->SetTransform(GetTransform());
            modelData->Processing();
        }
    }

    Object::Processing(); // update children
}
