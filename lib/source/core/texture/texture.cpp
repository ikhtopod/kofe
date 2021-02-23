#include "texture/texture.h"

#include "app_exceptions.h"


namespace {

static const glm::vec4 TEXTURE_BORDER_COLOR { .0f, .0f, .0f, 1.f };
static const GLsizei BUFFER_SIZE { 1 };
static const GLint MIPMAP_LEVEL { 0 };
static const GLint BORDER { 0 }; // always zero (legacy)
static const GLenum DEFAULT_TEXTURE_UNIT { GL_TEXTURE0 };
static const GLenum LAST_TEXTURE_UNIT { GL_TEXTURE31 };
static const bool DEFAULT_FLIP_VERTICAL { true };

} // namespace


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

void Texture::InitTexture(const std::filesystem::path& texturePath, bool flipVertical) {
    glGenTextures(BUFFER_SIZE, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    InitTextureWrapParameters();
    InitTextureFilterParameter();

    stbi_set_flip_vertically_on_load(static_cast<int>(flipVertical));

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
    Texture { texturePath, DEFAULT_TEXTURE_UNIT } {}

Texture::Texture(const std::filesystem::path& texturePath, GLenum textureUnit) :
    Texture { texturePath, textureUnit, DEFAULT_FLIP_VERTICAL } {}

Texture::Texture(const std::filesystem::path& texturePath, GLenum textureUnit, bool flipVertical) :
    m_textureChannelComponents { TextureChannelComponents::RGBA },
    m_textureUnit { textureUnit },
    m_samplePosition {},
    m_width {},
    m_height {},
    m_channels {},
    tex {} {
    InitTexture(texturePath, flipVertical);
}

Texture::~Texture() {
    glDeleteTextures(BUFFER_SIZE, &tex);
}

void Texture::Unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLenum Texture::GetTextureUnit() const {
    return m_textureUnit;
}

void Texture::SetTextureUnit(GLenum textureUnit) {
    m_textureUnit = textureUnit;
    UpdateSamplePosition();
}

int Texture::GetSamplePosition() const {
    return m_samplePosition;
}

void Texture::UpdateSamplePosition() {
    m_samplePosition = GetTextureUnit() - DEFAULT_TEXTURE_UNIT;
}

GLenum Texture::NextTextureUnit() const {
    if (m_textureUnit == LAST_TEXTURE_UNIT) {
        throw TextureException { "Cannot use next texture unit" };
    }

    return m_textureUnit + 1;
}

void Texture::Processing() {
    glActiveTexture(m_textureUnit);
    glBindTexture(GL_TEXTURE_2D, tex);
}
