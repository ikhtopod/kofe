#ifndef TEXTURE_H
#define TEXTURE_H

#include "iprocess.h"

#include <glm/glm.hpp>
#include <stb_image.h>

#include <cstddef>
#include <filesystem>


enum class TextureChannelComponents : int {
    DEFAULT = STBI_default,
    GREY = STBI_grey,
    GREY_ALPHA = STBI_grey_alpha,
    RGB = STBI_rgb,
    RGBA = STBI_rgb_alpha,
};


class Texture final : public IProcess {
    static const glm::vec4 TEXTURE_BORDER_COLOR;
    static const int TEXTURE_WRAP;

    static const size_t BUFFER_SIZE;
    static const int MIPMAP_LEVEL;
    static const int BORDER;

private:
    const TextureChannelComponents m_textureChannelComponents;
    const unsigned m_textureUnit; // GL_TEXTURE0 - always activated by default
    bool m_flipVertical;

    int m_width;
    int m_height;
    int m_channels;

    unsigned int tex;

private:
    void InitTextureWrapParameters() const;
    void InitTextureFilterParameter() const;
    void InitTexture(const std::filesystem::path& texturePath);

public:
    Texture() = delete;
    Texture(const Texture&) = delete;
    Texture(Texture&&) = delete;
    Texture& operator=(const Texture&) = delete;
    Texture& operator=(Texture&&) = delete;
    ~Texture();

    explicit Texture(const std::filesystem::path& texturePath);

private:
    void Unbind() const;

public: /* IProcess */
    void Processing() override;

    void InvertVertical();
    unsigned NextTextureUnit() const;
};

#endif // TEXTURE_H
