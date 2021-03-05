#ifndef MODEL_H
#define MODEL_H

#include "object.h"

#include <filesystem>
#include <vector>


class Model : public Object {
public:
    friend void swap(Model&, Model&);

protected:
    std::vector<std::filesystem::path> m_lods;
    float m_distanceStep;

public:
    Model() = delete;

public:
    Model(const Model& other);
    Model(Model&& other) noexcept;
    Model& operator=(const Model& other);
    Model& operator=(Model&& other) noexcept;
    virtual ~Model();

public:
    explicit Model(const std::filesystem::path& path);
    explicit Model(std::filesystem::path path,
                   std::filesystem::path textureDirectory);

public:
    std::vector<std::filesystem::path>& GetLODs();
    const std::vector<std::filesystem::path>& GetLODs() const;

private:
    // Add after the calculation of the number of LODs.
    void UpdateDistanceStep();
    void UpdateLODs(const std::filesystem::path& path);
    float GetDistanceToCamera() const;
    size_t GetCurrentLodId() const;

public: /* IProcess */
    void Processing() override;
};


void swap(Model& lhs, Model& rhs);

#endif // MODEL_H
