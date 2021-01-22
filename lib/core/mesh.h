#ifndef MESH_H
#define MESH_H

#include "iprocess.h"
#include "transformable.h"
#include "vertex.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <cstddef>
#include <vector>


enum class AttribIndex : GLuint {
    POSITION,
    TEXTURE,
};


class Mesh :
        public IProcess,
        public Transformable
{
private:
    static const GLsizei BUFFER_SIZE { 1 };

public:
    friend void swap(Mesh&, Mesh&);

private:
    GLuint vao, vbo, ebo;

    std::vector<Vertex> m_verices;
    std::vector<GLuint> m_indices;

    size_t m_materialId;

private:
    void Init();
    void Free();

public:
    Mesh() = delete;
    Mesh(const Mesh&) = delete;
    Mesh(Mesh&&) noexcept = delete;
    Mesh& operator=(const Mesh&) = delete;
    Mesh& operator=(Mesh&&) noexcept = delete;

public:
    Mesh(const std::vector<Vertex>& verices, const std::vector<GLuint>& indices);
    Mesh(std::vector<Vertex>&& verices, std::vector<GLuint>&& indices) noexcept;
    ~Mesh();

public:
    size_t GetMaterialId() const;
    void SetMaterialId(size_t materialId);

public: /* IProcess */
    void Processing() override;
};

void swap(Mesh& lhs, Mesh& rhs);

#endif // MESH_H
