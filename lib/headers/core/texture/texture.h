#ifndef TEXTURE_H
#define TEXTURE_H

#include "interface/iprocess.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
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
private:
    const TextureChannelComponents m_textureChannelComponents;
    GLenum m_textureUnit; // GL_TEXTURE0 - always activated by default
    bool m_flipVertical;

    int m_width;
    int m_height;
    int m_channels;

    GLuint tex;

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

public:
    virtual ~Texture();

    explicit Texture(const std::filesystem::path& texturePath);
    explicit Texture(const std::filesystem::path& texturePath, GLenum textureUnit);

private:
    void Unbind() const;

public:
    GLenum GetTextureUnit() const;
    void SetTextureUnit(GLenum textureUnit);

    void InvertVertical();
    GLenum NextTextureUnit() const;

public: /* IProcess */
    void Processing() override;
};

#endif // TEXTURE_H
