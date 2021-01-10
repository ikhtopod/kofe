#include "vertex.h"


Vertex::Vertex() :
    Vertex { glm::vec3 {}, glm::vec2 {}, GLuint {} } {}

Vertex::Vertex(const Vertex& other) :
    m_position { other.m_position },
    m_texture { other.m_texture },
    m_index { other.m_index } {}

Vertex::Vertex(Vertex&& other) noexcept :
    m_position { std::move(other.m_position) },
    m_texture { std::move(other.m_texture) },
    m_index { std::move(other.m_index) } {}

Vertex& Vertex::operator=(const Vertex& other) {
    Vertex tmp { other };
    swap(*this, tmp);
    return *this;
}

Vertex& Vertex::operator=(Vertex&& other) noexcept {
    if (this != &other) {
        m_position = std::move(other.m_position);
        m_texture = std::move(other.m_texture);
        m_index = std::move(other.m_index);
    }

    return *this;
}

Vertex::Vertex(glm::vec3 position, glm::vec2 texture, GLuint index) :
    m_position { std::move(position) },
    m_texture { std::move(texture) },
    m_index { std::move(index) } {}

bool Vertex::operator==(const Vertex& other) const {
    return (m_position == other.m_position) &&
            (m_texture == other.m_texture) &&
            (m_index == other.m_index);
}

glm::vec3 Vertex::GetPosition() const { return m_position; }

void Vertex::SetPosition(const glm::vec3& position) {
    m_position = position;
}

glm::vec2 Vertex::GetTexture() const { return m_texture; }

void Vertex::SetTexture(const glm::vec2& texture) {
    m_texture = texture;
}

GLuint Vertex::GetIndex() const { return m_index; }

void Vertex::SetIndex(GLuint index) {
    m_index = index;
}

void swap(Vertex& lhs, Vertex& rhs) {
    if (&lhs == &rhs) return;

    using std::swap;
    swap(lhs.m_position, rhs.m_position);
    swap(lhs.m_texture, rhs.m_texture);
    swap(lhs.m_index, rhs.m_index);
}
