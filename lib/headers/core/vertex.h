#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>


struct Vertex final {
public:
    glm::vec3 position;
    glm::vec3 normal;
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

public:
    Vertex(glm::vec3 pos, glm::vec3 nrm, glm::vec2 tex);

    bool operator==(const Vertex& other) const;
};

void swap(Vertex& lhs, Vertex& rhs);

#endif // VERTEX_H
