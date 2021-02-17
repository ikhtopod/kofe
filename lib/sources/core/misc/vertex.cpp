#include "misc/vertex.h"

#include <utility>


void swap(Vertex& lhs, Vertex& rhs) {
    if (&lhs == &rhs) return;

    using std::swap;

    swap(lhs.position, rhs.position);
    swap(lhs.normal, rhs.normal);
    swap(lhs.texture, rhs.texture);
}


Vertex::Vertex() :
    Vertex {
        glm::vec3 {},
        glm::vec3 {},
        glm::vec2 {}
    } {}

Vertex::Vertex(const Vertex& other) :
    position { other.position },
    normal { other.normal },
    texture { other.texture } {}

Vertex::Vertex(Vertex&& other) noexcept :
    position { std::move(other.position) },
    normal { std::move(other.normal) },
    texture { std::move(other.texture) } {}

Vertex& Vertex::operator=(const Vertex& other) {
    if (this != &other) {
        position = other.position;
        normal = other.normal;
        texture = other.texture;
    }

    return *this;
}

Vertex& Vertex::operator=(Vertex&& other) noexcept {
    if (this != &other) {
        position = std::move(other.position);
        normal = std::move(other.normal);
        texture = std::move(other.texture);
    }

    return *this;
}

Vertex::Vertex(glm::vec3 pos, glm::vec3 nrm, glm::vec2 tex) :
    position { std::move(pos) },
    normal { std::move(nrm) },
    texture { std::move(tex) } {}

bool Vertex::operator==(const Vertex& other) const {
    return (position == other.position) &&
           (normal == other.normal) &&
           (texture == other.texture);
}
