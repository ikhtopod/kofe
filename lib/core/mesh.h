#ifndef MESH_H
#define MESH_H

#include "iprocess.h"
#include "vertex.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <cstddef>
#include <vector>
#include <utility>


enum class AttribIndex : GLuint {
    POSITION,
    TEXTURE,
};


class Mesh : public IProcess {
    static const GLsizei BUFFER_SIZE { 1 };

public:
    friend void swap(Mesh&, Mesh&);

private:
    GLuint vao, vbo, ebo;

    std::vector<Vertex> m_verices;
    std::vector<GLuint> m_indices;

private:
    void Init();
    void Free();

public:
    Mesh() = delete;
    Mesh(const Mesh&) = delete;
    Mesh(Mesh&&) noexcept = delete;
    Mesh& operator=(const Mesh&) = delete;
    Mesh& operator=(Mesh&&) noexcept = delete;

    Mesh(const std::vector<Vertex>& verices, const std::vector<GLuint>& indices);
    Mesh(std::vector<Vertex>&& verices, std::vector<GLuint>&& indices) noexcept;
    ~Mesh();

public: /* IProcess */
    void Processing() override;
};

void swap(Mesh& lhs, Mesh& rhs);

#endif // MESH_H
