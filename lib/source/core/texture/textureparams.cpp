#include "texture/textureparams.h"

#include <utility>


void swap(TextureParams& lhs, TextureParams& rhs) {
    if (&lhs == &rhs) return;

    using std::swap;

    swap(lhs.m_path, rhs.m_path);
    swap(lhs.m_unit, rhs.m_unit);
}


TextureParams::TextureParams(const TextureParams& other) :
    m_path { other.m_path },
    m_unit { other.m_unit } {}

TextureParams::TextureParams(TextureParams&& other) noexcept :
    m_path { std::move(other.m_path) },
    m_unit { std::move(other.m_unit) } {}

TextureParams::TextureParams(const std::filesystem::path& path) :
    TextureParams { path, GL_TEXTURE0 } {}

TextureParams::TextureParams(const std::filesystem::path& path, GLenum unit) :
    m_path { path },
    m_unit { unit } {}

TextureParams& TextureParams::operator=(const TextureParams& other) {
    if (this != &other) {
        m_path = other.m_path;
        m_unit = other.m_unit;
    }

    return *this;
}

TextureParams& TextureParams::operator=(TextureParams&& other) noexcept {
    if (this != &other) {
        m_path = std::move(other.m_path);
        m_unit = std::move(other.m_unit);
    }

    return *this;
}

std::filesystem::path TextureParams::GetPath() const {
    return m_path;
}

GLenum TextureParams::GetUnit() const {
    return m_unit;
}

void TextureParams::SetPath(const std::filesystem::path& path) {
    m_path = path;
}

void TextureParams::SetUnit(GLenum unit) {
    m_unit = unit;
}
