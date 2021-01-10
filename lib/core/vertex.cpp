#include "vertex.h"


Vertex::Vertex() :
    Vertex { glm::vec3 {}, glm::vec2 {} } {}

Vertex::Vertex(const Vertex& other) :
    position { other.position },
    texture { other.texture } {}

Vertex::Vertex(Vertex&& other) noexcept :
    position { std::move(other.position) },
    texture { std::move(other.texture) } {}

Vertex& Vertex::operator=(const Vertex& other) {
    Vertex tmp { other };
    swap(*this, tmp);
    return *this;
}

Vertex& Vertex::operator=(Vertex&& other) noexcept {
    if (this != &other) {
        position = std::move(other.position);
        texture = std::move(other.texture);
    }

    return *this;
}

Vertex::Vertex(glm::vec3 pos, glm::vec2 tex) :
    position { std::move(pos) },
    texture { std::move(tex) } {}

bool Vertex::operator==(const Vertex& other) const {
    return (position == other.position) &&
            (texture == other.texture);;
}

void swap(Vertex& lhs, Vertex& rhs) {
    if (&lhs == &rhs) return;

    using std::swap;
    swap(lhs.position, rhs.position);
    swap(lhs.texture, rhs.texture);
}
