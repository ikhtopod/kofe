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

    static const std::filesystem::path DEFAULT_VERTEX_PATH;
    static const std::filesystem::path DEFAULT_FRAGMENT_PATH;

    static constexpr GLuint INFOLOG_SIZE { 512 };
    static constexpr GLint LOCATION_ERROR_FLAG { -1 };

private:
    GLuint m_program;
    UniformProcessing m_uniformProcessingFunc;

public:
    Shader();
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

    void SetBool(const std::string& uniformName, bool value, bool isArray = false) const;
    void SetInt(const std::string& uniformName, GLint value, bool isArray = false) const;
    void SetUInt(const std::string& uniformName, GLuint value, bool isArray = false) const;
    void SetFloat(const std::string& uniformName, GLfloat value, bool isArray = false) const;
    void SetDouble(const std::string& uniformName, GLdouble value, bool isArray = false) const;

    void SetVec1(const std::string& uniformName, const glm::vec1& value, bool isArray = false) const;
    void SetVec2(const std::string& uniformName, const glm::vec2& value, bool isArray = false) const;
    void SetVec3(const std::string& uniformName, const glm::vec3& value, bool isArray = false) const;
    void SetVec4(const std::string& uniformName, const glm::vec4& value, bool isArray = false) const;

    void SetMat2(const std::string& uniformName, const glm::mat2& value, bool isArray = false) const;
    void SetMat3(const std::string& uniformName, const glm::mat3& value, bool isArray = false) const;
    void SetMat4(const std::string& uniformName, const glm::mat4& value, bool isArray = false) const;

public: /* IProcess */
    void Processing() override;
};

#endif // SHADER_H
