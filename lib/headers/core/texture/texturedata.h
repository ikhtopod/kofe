#ifndef TEXTUREDATA_H
#define TEXTUREDATA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <filesystem>


class TextureData final {
private:
    std::filesystem::path m_path;
    GLenum m_unit;

public:
    friend void swap(TextureData&, TextureData&);

public:
    TextureData() = delete;

public:
    TextureData(const TextureData& other);
    TextureData(TextureData&& other) noexcept;
    TextureData& operator=(const TextureData& other);
    TextureData& operator=(TextureData&& other) noexcept;
    ~TextureData() = default;

    explicit TextureData(const std::filesystem::path& path);
    explicit TextureData(const std::filesystem::path& path, GLenum unit);

public:
    std::filesystem::path GetPath() const;
    GLenum GetUnit() const;

    void SetPath(const std::filesystem::path& path);
    void SetUnit(GLenum unit);
};


void swap(TextureData& lhs, TextureData& rhs);

#endif // TEXTUREDATA_H
