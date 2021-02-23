#ifndef TEXTURESTORAGE_H
#define TEXTURESTORAGE_H

#include "texture/texture.h"
#include "texture/texturedata.h"
#include "interface/icanbeeverywhere.h"

#include <unordered_map>
#include <initializer_list>
#include <string>
#include <memory>


class TextureStorage final :
    public ICanBeEverywhere {
private:
    using StoredType = Texture;
    using KeyType = std::string;
    using ValueType = std::shared_ptr<StoredType>;

private:
    mutable std::unordered_map<KeyType, ValueType> m_textures {};

public:
    TextureStorage(const TextureStorage&) = delete;
    TextureStorage(TextureStorage&&) noexcept = delete;
    TextureStorage& operator=(const TextureStorage&) = delete;
    TextureStorage& operator=(TextureStorage&&) noexcept = delete;

public:
    TextureStorage();
    ~TextureStorage();

    TextureStorage(const std::initializer_list<std::filesystem::path>& paths);

public:
    ValueType Get(std::filesystem::path path);
    const ValueType Get(std::filesystem::path path) const;

    ValueType Get(const TextureData& textureData);
    const ValueType Get(const TextureData& textureData) const;

    ValueType Get(std::filesystem::path path, GLenum textureUnit);
    const ValueType Get(std::filesystem::path path, GLenum textureUnit) const;

    ValueType GetDefaultTexture();
    const ValueType GetDefaultTexture() const;

    ValueType GetDefaultTexture(GLenum textureUnit);
    const ValueType GetDefaultTexture(GLenum textureUnit) const;

    std::filesystem::path GetDefaultTexturePath() const;
};

#endif // TEXTURESTORAGE_H
