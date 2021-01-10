#ifndef VERTEX_H
#define VERTEX_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <utility>


struct Vertex final {
public:
    glm::vec3 position;
    glm::vec2 texture;

public:
    friend void swap(Vertex&, Vertex&);

public:
    Vertex();
    Vertex(const Vertex& other);
    Vertex(Vertex&& other) noexcept;
    Vertex& operator=(const Vertex& other);
    Vertex& operator=(Vertex&& other) noexcept;
    ~Vertex() = default;

    Vertex(glm::vec3 pos, glm::vec2 tex);

    bool operator==(const Vertex& other) const;
};

void swap(Vertex& lhs, Vertex& rhs);

#endif // VERTEX_H
