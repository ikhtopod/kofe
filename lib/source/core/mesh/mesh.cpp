#include "mesh/mesh.h"

#include "everywhere.h"

#include <utility>


namespace {

static const GLsizei BUFFER_SIZE { 1 };

} // namespace

void swap(Mesh& lhs, Mesh& rhs) {
    if (&lhs == &rhs) return;

    using std::swap;

    swap(lhs.vao, rhs.vao);
    swap(lhs.vbo, rhs.vbo);
    swap(lhs.ebo, rhs.ebo);
    swap(lhs.m_verices, rhs.m_verices);
    swap(lhs.m_indices, rhs.m_indices);
    swap(lhs.m_materialId, rhs.m_materialId);
    swap(lhs.m_drawingMode, rhs.m_drawingMode);
}


Mesh::~Mesh() {
    Free();
}

Mesh::Mesh(const std::vector<Vertex>& verices, const std::vector<GLuint>& indices) :
    Object {},
    vao {}, vbo {}, ebo {},
    m_verices { verices },
    m_indices { indices },
    m_materialId {},
    m_drawingMode { MeshDrawingMode::TRIANGLES } {
    Init();
}

Mesh::Mesh(std::vector<Vertex>&& verices, std::vector<GLuint>&& indices) noexcept :
    Object {},
    vao {}, vbo {}, ebo {},
    m_verices { std::move(verices) },
    m_indices { std::move(indices) },
    m_materialId {},
    m_drawingMode { MeshDrawingMode::TRIANGLES } {
    Init();
}

size_t Mesh::GetMaterialId() const {
    return m_materialId;
}

void Mesh::SetMaterialId(size_t materialId) {
    m_materialId = materialId;
}

MeshDrawingMode Mesh::GetDrawingMode() const {
    return m_drawingMode;
}

void Mesh::SetDrawingMode(MeshDrawingMode drawingMode) {
    m_drawingMode = drawingMode;
}

void Mesh::SetDrawingMode(GLenum drawingMode) {
    m_drawingMode = static_cast<MeshDrawingMode>(drawingMode);
}

void Mesh::Init() {
    glGenVertexArrays(::BUFFER_SIZE, &vao);
    glGenBuffers(::BUFFER_SIZE, &vbo);
    glGenBuffers(::BUFFER_SIZE, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 m_verices.size() * sizeof(Vertex),
                 &m_verices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 m_indices.size() * sizeof(GLuint),
                 &m_indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(static_cast<GLuint>(AttribIndex::POSITION),
                          3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          reinterpret_cast<void*>(0));

    glVertexAttribPointer(static_cast<GLuint>(AttribIndex::NORMAL),
                          3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          reinterpret_cast<void*>(offsetof(Vertex, normal)));

    glVertexAttribPointer(static_cast<GLuint>(AttribIndex::TEXTURE),
                          2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          reinterpret_cast<void*>(offsetof(Vertex, texture)));

    glBindVertexArray(0);
}

void Mesh::Free() {
    glDeleteVertexArrays(::BUFFER_SIZE, &vao);
    glDeleteBuffers(::BUFFER_SIZE, &vbo);
    glDeleteBuffers(::BUFFER_SIZE, &ebo);

    m_verices.clear();
    m_indices.clear();
}

void Mesh::Processing() {
    auto material =
        Everywhere::Instance().Get<MaterialStorage>().GetMaterials().At(m_materialId);
    material->SetParentTransform(GetGlobalTransform());
    material->Processing();

    glBindVertexArray(vao);

    glEnableVertexAttribArray(static_cast<GLuint>(AttribIndex::POSITION));
    glEnableVertexAttribArray(static_cast<GLuint>(AttribIndex::NORMAL));
    glEnableVertexAttribArray(static_cast<GLuint>(AttribIndex::TEXTURE));

    glDrawElements(static_cast<GLenum>(m_drawingMode),
                   static_cast<GLsizei>(m_indices.size()),
                   GL_UNSIGNED_INT, reinterpret_cast<void*>(0));

    glDisableVertexAttribArray(static_cast<GLuint>(AttribIndex::TEXTURE));
    glDisableVertexAttribArray(static_cast<GLuint>(AttribIndex::NORMAL));
    glDisableVertexAttribArray(static_cast<GLuint>(AttribIndex::POSITION));

    Object::Processing(); // update children
}
