#ifndef SHADER_H
#define SHADER_H

#include "iprocess.h"
#include "globaltransformation.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <functional>
#include <filesystem>


class Shader final :
    public IProcess,
    public GlobalTransformation {
private:
    using UniformProcessing = std::function<void(Shader*)>;

    static const GLuint INFOLOG_SIZE { 512 };
    static constexpr GLint LOCATION_ERROR_FLAG { -1 };

private:
    GLuint m_program;
    UniformProcessing m_uniformProcessingFunc;

public:
    Shader() = delete;
    Shader(const Shader&) = delete;
    Shader(Shader&&) noexcept = delete;
    Shader& operator=(const Shader&) = delete;
    Shader& operator=(Shader&&) noexcept = delete;
    ~Shader();

    Shader(const std::filesystem::path& vertexPath,
           const std::filesystem::path& fragmentPath);

private:
    void CreateProgram(const std::filesystem::path& vertexPath,
                       const std::filesystem::path& fragmentPath);
    GLuint* CompileVertex(const std::filesystem::path& vertexPath);
    GLuint* CompileFragment(const std::filesystem::path& fragmentPath);
    void LinkShadersToProgram(GLuint* vertex, GLuint* fragment);
    void DeleteShaders(GLuint* vertex, GLuint* fragment);

public:
    void Use() const;

    void SetUniformProcessingFunc(const UniformProcessing& func);

    void CheckLocationError(GLint location, const std::string& uniformName) const;

    void SetBool(const std::string& uniformName, bool value) const;
    void SetInt(const std::string& uniformName, GLint value) const;
    void SetUInt(const std::string& uniformName, GLuint value) const;
    void SetFloat(const std::string& uniformName, GLfloat value) const;
    void SetDouble(const std::string& uniformName, GLdouble value) const;

    void SetVec1(const std::string& uniformName, const glm::vec1& value) const;
    void SetVec2(const std::string& uniformName, const glm::vec2& value) const;
    void SetVec3(const std::string& uniformName, const glm::vec3& value) const;
    void SetVec4(const std::string& uniformName, const glm::vec4& value) const;

    void SetMat2(const std::string& uniformName, const glm::mat2& value) const;
    void SetMat3(const std::string& uniformName, const glm::mat3& value) const;
    void SetMat4(const std::string& uniformName, const glm::mat4& value) const;

public: /* IProcess */
    void Processing() override;
};

#endif // SHADER_H
