#ifndef MODEL_H
#define MODEL_H

#include "object.h"

#include <filesystem>


class Model : public Object {
protected:
    std::filesystem::path m_pathId;

public:
    Model() = delete;

public:
    Model(const Model& other);
    Model(Model&& other) noexcept;
    Model& operator=(const Model& other);
    Model& operator=(Model&& other) noexcept;
    virtual ~Model() = default;

public:
    explicit Model(const std::filesystem::path& path);
    explicit Model(const std::filesystem::path& path,
                   const std::filesystem::path& textureDirectory);

public:
    friend void swap(Model&, Model&);

public: /* IProcess */
    void Processing() override;
};


void swap(Model& lhs, Model& rhs);

#endif // MODEL_H
