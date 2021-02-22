#ifndef MESH_H
#define MESH_H

#include "object/object.h"
#include "misc/vertex.h"

#include <glad/glad.h>

#include <cstddef>
#include <vector>


enum class AttribIndex : GLuint {
    POSITION,
    NORMAL,
    TEXTURE,
};

enum class MeshDrawingMode : GLenum {
    POINTS = GL_POINTS,
    LINES = GL_LINES,
    LINE_LOOP = GL_LINE_LOOP,
    LINE_STRIP = GL_LINE_STRIP,
    TRIANGLES = GL_TRIANGLES,
    TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
    TRIANGLE_FAN = GL_TRIANGLE_FAN
};

class Mesh : public Object {
public:
    friend void swap(Mesh&, Mesh&);

private:
    GLuint vao, vbo, ebo;

    std::vector<Vertex> m_verices;
    std::vector<GLuint> m_indices;

    size_t m_materialId;
    MeshDrawingMode m_drawingMode;

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
    virtual ~Mesh();

public:
    size_t GetMaterialId() const;
    void SetMaterialId(size_t materialId);

    MeshDrawingMode GetDrawingMode() const;
    void SetDrawingMode(MeshDrawingMode drawingMode);
    void SetDrawingMode(GLenum drawingMode);

public: /* IProcess */
    void Processing() override;
};


void swap(Mesh& lhs, Mesh& rhs);

#endif // MESH_H
