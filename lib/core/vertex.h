#ifndef VERTEX_H
#define VERTEX_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <utility>


struct Vertex final {
private:
    glm::vec3 m_position;
    glm::vec2 m_texture;
    GLuint m_index;

public:
    friend void swap(Vertex&, Vertex&);

public:
    Vertex();
    Vertex(const Vertex& other);
    Vertex(Vertex&& other) noexcept;
    Vertex& operator=(const Vertex& other);
    Vertex& operator=(Vertex&& other) noexcept;
    ~Vertex() = default;

    Vertex(glm::vec3 position, glm::vec2 texture, GLuint index);

    bool operator==(const Vertex& other) const;

    glm::vec3 GetPosition() const;
    glm::vec2 GetTexture() const;
    GLuint GetIndex() const;
};

void swap(Vertex& lhs, Vertex& rhs);

#endif // VERTEX_H
