#ifndef TEXTUREPARAMS_H
#define TEXTUREPARAMS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <filesystem>


class TextureParams final {
private:
    std::filesystem::path m_path;
    GLenum m_unit;

public:
    friend void swap(TextureParams&, TextureParams&);

public:
    TextureParams() = delete;

public:
    TextureParams(const TextureParams& other);
    TextureParams(TextureParams&& other) noexcept;
    TextureParams& operator=(const TextureParams& other);
    TextureParams& operator=(TextureParams&& other) noexcept;
    ~TextureParams() = default;

    explicit TextureParams(const std::filesystem::path& path);
    explicit TextureParams(const std::filesystem::path& path, GLenum unit);

public:
    std::filesystem::path GetPath() const;
    GLenum GetUnit() const;

    void SetPath(const std::filesystem::path& path);
    void SetUnit(GLenum unit);
};


void swap(TextureParams& lhs, TextureParams& rhs);

#endif // TEXTUREPARAMS_H
