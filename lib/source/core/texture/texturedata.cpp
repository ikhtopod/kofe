#include "texture/texturedata.h"

#include <utility>


void swap(TextureData& lhs, TextureData& rhs) {
    if (&lhs == &rhs) return;

    using std::swap;

    swap(lhs.m_path, rhs.m_path);
    swap(lhs.m_unit, rhs.m_unit);
}


TextureData::TextureData(const TextureData& other) :
    m_path { other.m_path },
    m_unit { other.m_unit } {}

TextureData::TextureData(TextureData&& other) noexcept :
    m_path { std::move(other.m_path) },
    m_unit { std::move(other.m_unit) } {}

TextureData::TextureData(const std::filesystem::path& path) :
    TextureData { path, GL_TEXTURE0 } {}

TextureData::TextureData(const std::filesystem::path& path, GLenum unit) :
    m_path { path },
    m_unit { unit } {}

TextureData& TextureData::operator=(const TextureData& other) {
    if (this != &other) {
        m_path = other.m_path;
        m_unit = other.m_unit;
    }

    return *this;
}

TextureData& TextureData::operator=(TextureData&& other) noexcept {
    if (this != &other) {
        m_path = std::move(other.m_path);
        m_unit = std::move(other.m_unit);
    }

    return *this;
}

std::filesystem::path TextureData::GetPath() const {
    return m_path;
}

GLenum TextureData::GetUnit() const {
    return m_unit;
}

void TextureData::SetPath(const std::filesystem::path& path) {
    m_path = path;
}

void TextureData::SetUnit(GLenum unit) {
    m_unit = unit;
}
