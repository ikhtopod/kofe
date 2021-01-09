#ifndef SHADER_H
#define SHADER_H

#include "iprocess.h"

#include <glm/glm.hpp>

#include <functional>
#include <filesystem>


class Shader final : public IProcess {
    using UniformProcessing = std::function<void(Shader*)>;

    static const unsigned INFOLOG_SIZE { 512 };
    static constexpr int LOCATION_ERROR_FLAG { -1 };

private:
    unsigned m_program;
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
    unsigned* CompileVertex(const std::filesystem::path& vertexPath);
    unsigned* CompileFragment(const std::filesystem::path& fragmentPath);
    void LinkShadersToProgram(unsigned* vertex, unsigned* fragment);
    void DeleteShaders(unsigned* vertex, unsigned* fragment);

    void CheckLocationError(int location, const std::string& uniformName) const;

public:
    void Use() const;

    void SetUniformProcessingFunc(UniformProcessing& func);

    void SetBool(const std::string& uniformName, bool value) const;
    void SetInt(const std::string& uniformName, int value) const;
    void SetFloat(const std::string& uniformName, float value) const;

    void SetVec1(const std::string& uniformName, glm::vec1 value) const;
    void SetVec2(const std::string& uniformName, glm::vec2 value) const;
    void SetVec3(const std::string& uniformName, glm::vec3 value) const;
    void SetVec4(const std::string& uniformName, glm::vec4 value) const;

    void SetMat2(const std::string& uniformName, const glm::mat2& value) const;
    void SetMat3(const std::string& uniformName, const glm::mat3& value) const;
    void SetMat4(const std::string& uniformName, const glm::mat4& value) const;

public: /* IProcess */
    void Processing() override;
};

#endif // SHADER_H
