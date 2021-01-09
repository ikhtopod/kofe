#include "texture.h"

#include "app_exceptions.h"

#include <glad/glad.h>


const glm::vec4 Texture::TEXTURE_BORDER_COLOR { .0f, .0f, .0f, 1.f };
const int Texture::TEXTURE_WRAP { GL_CLAMP_TO_EDGE };
const size_t Texture::BUFFER_SIZE { 1 };
const int Texture::MIPMAP_LEVEL { 0 };
const int Texture::BORDER { 0 }; // always zero (legacy)

void Texture::InitTextureWrapParameters() const {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    GLint currentTextureWrap {};
    glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, &currentTextureWrap);

    if (currentTextureWrap == GL_CLAMP_TO_BORDER) {
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, &TEXTURE_BORDER_COLOR[0]);
    }
}

void Texture::InitTextureFilterParameter() const {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // firstTexture minimaze
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // firstTexture maximize
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 7);
}

void Texture::InitTexture(const std::filesystem::path& texturePath) {
    glGenTextures(BUFFER_SIZE, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    InitTextureWrapParameters();
    InitTextureFilterParameter();

    stbi_set_flip_vertically_on_load(static_cast<int>(m_flipVertical));

    uint8_t* data = stbi_load(texturePath.c_str(), &m_width, &m_height, &m_channels,
                              static_cast<int>(m_textureChannelComponents));

    if (!data) {
        glDeleteTextures(BUFFER_SIZE, &tex);
        Unbind();
        throw TextureException { "Cannot load image \"" + texturePath.string() + '"' };
    }

    GLenum format { GL_RGB };
    if (m_textureChannelComponents == TextureChannelComponents::RGBA ||
            m_textureChannelComponents == TextureChannelComponents::GREY_ALPHA) {
        format = GL_RGBA;
    }

    glTexImage2D(GL_TEXTURE_2D, MIPMAP_LEVEL, GL_RGB, m_width, m_height, BORDER, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D); // generate all mipmap levels

    stbi_image_free(data);
    Unbind();
}

Texture::Texture(const std::filesystem::path& texturePath) :
    m_textureChannelComponents { TextureChannelComponents::RGBA },
    m_textureUnit { GL_TEXTURE0 },
    m_flipVertical { false },
    m_width {},
    m_height {},
    m_channels {},
    tex {}
{
    InitTexture(texturePath);
}

Texture::~Texture() {
    glDeleteTextures(BUFFER_SIZE, &tex);
}

void Texture::Unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::InvertVertical() {
    m_flipVertical = !m_flipVertical;
}

unsigned Texture::NextTextureUnit() const {
    if (m_textureUnit == GL_TEXTURE31) {
        throw TextureException { "Cannot use next texture unit" };
    }

    return m_textureUnit + 1;
}

void Texture::Processing() {
    glActiveTexture(m_textureUnit);
    glBindTexture(GL_TEXTURE_2D, tex);
}
