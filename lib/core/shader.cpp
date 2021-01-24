#include "shader.h"

#include "app_exceptions.h"
#include "fs.h"
#include "everywhere.h"

#include <glm/gtc/type_ptr.hpp>

#include <string>


Shader::Shader(const std::filesystem::path& vertexPath,
               const std::filesystem::path& fragmentPath) :
    GlobalTransformation {},
    m_program {},
    m_uniformProcessingFunc {}
{
    m_uniformProcessingFunc = [] (Shader*) {};
    CreateProgram(vertexPath, fragmentPath);
}

Shader::~Shader() { glDeleteProgram(m_program); }

void Shader::CreateProgram(const std::filesystem::path& vertexPath,
                           const std::filesystem::path& fragmentPath)
{
    GLuint* vertex { nullptr };
    GLuint* fragment { nullptr };

    try {
        vertex = CompileVertex(vertexPath);
        fragment = CompileFragment(fragmentPath);
        LinkShadersToProgram(vertex, fragment);
    } catch (const ShaderException* e) {
        DeleteShaders(vertex, fragment);
        glDeleteProgram(m_program);
        throw e;
    }

    DeleteShaders(vertex, fragment);
}

GLuint* Shader::CompileVertex(const std::filesystem::path& vertexPath) {
    GLuint* vertex = new GLuint { glCreateShader(GL_VERTEX_SHADER) };

    std::string vertexSourceCode = filesystem::GetContentFile(vertexPath);
    const GLchar* vertexSourcePtr = vertexSourceCode.c_str();

    glShaderSource(*vertex, 1, &vertexSourcePtr, nullptr);
    glCompileShader(*vertex);

    vertexSourceCode.clear();

    GLint checkSuccess {};
    glGetShaderiv(*vertex, GL_COMPILE_STATUS, &checkSuccess);

    if (!checkSuccess) {
        GLchar message[INFOLOG_SIZE];
        glGetShaderInfoLog(*vertex, INFOLOG_SIZE, nullptr, message);
        throw VertexShaderException("Compile error: " + std::string { message });
    }

    return vertex;
}

GLuint* Shader::CompileFragment(const std::filesystem::path& fragmentPath) {
    GLuint* fragment = new GLuint { glCreateShader(GL_FRAGMENT_SHADER) };

    std::string fragmentSourceCode = filesystem::GetContentFile(fragmentPath);
    const GLchar* fragmentSourcePtr = fragmentSourceCode.c_str();

    glShaderSource(*fragment, 1, &fragmentSourcePtr, nullptr);
    glCompileShader(*fragment);

    fragmentSourceCode.clear();

    GLint checkSuccess {};
    glGetShaderiv(*fragment, GL_COMPILE_STATUS, &checkSuccess);

    if (!checkSuccess) {
        GLchar message[INFOLOG_SIZE];
        glGetShaderInfoLog(*fragment, INFOLOG_SIZE, nullptr, message);
        throw FragmentShaderException("Compile error: " + std::string { message });
    }

    return fragment;
}

void Shader::LinkShadersToProgram(GLuint* vertex, GLuint* fragment) {
    m_program = glCreateProgram();

    glAttachShader(m_program, *vertex);
    glAttachShader(m_program, *fragment);

    glLinkProgram(m_program);

    GLint checkSuccess {};
    glGetProgramiv(m_program, GL_LINK_STATUS, &checkSuccess);

    if (!checkSuccess) {
        DeleteShaders(vertex, fragment);

        GLchar message[INFOLOG_SIZE];
        glGetProgramInfoLog(m_program, INFOLOG_SIZE, nullptr, message);
        throw ProgramShaderException("Link error: " + std::string { message });
    }
}

void Shader::DeleteShaders(GLuint* vertex, GLuint* fragment) {
    for (auto* shader : { vertex, fragment }) {
        if (shader) {
            glDeleteShader(*shader);
            delete shader;
        }
    }
}

void Shader::Use() const {
    glUseProgram(m_program);
}

void Shader::SetUniformProcessingFunc(const Shader::UniformProcessing& func) {
    m_uniformProcessingFunc = func;
}

void Shader::SetBool(const std::string& uniformName, bool value) const {
    SetUInt(uniformName, static_cast<GLuint>(value));
}

void Shader::CheckLocationError(GLint location, const std::string& uniformName) const {
    if (location == LOCATION_ERROR_FLAG) {
        throw UniformShaderException("For uniform \"" + uniformName + "\" not found location");
    }
}

void Shader::SetInt(const std::string& uniformName, GLint value) const {
    GLint location = glGetUniformLocation(m_program, uniformName.c_str());
    CheckLocationError(location, uniformName);
    glUniform1i(location, value);
}

void Shader::SetUInt(const std::string& uniformName, GLuint value) const {
    GLint location = glGetUniformLocation(m_program, uniformName.c_str());
    CheckLocationError(location, uniformName);
    glUniform1ui(location, value);
}

void Shader::SetFloat(const std::string& uniformName, GLfloat value) const {
    GLint location = glGetUniformLocation(m_program, uniformName.c_str());
    CheckLocationError(location, uniformName);
    glUniform1f(location, value);
}

void Shader::SetDouble(const std::string& uniformName, GLdouble value) const {
    GLint location = glGetUniformLocation(m_program, uniformName.c_str());
    CheckLocationError(location, uniformName);
    glUniform1d(location, value);
}

void Shader::SetVec1(const std::string& uniformName, const glm::vec1& value) const {
    GLint location = glGetUniformLocation(m_program, uniformName.c_str());
    CheckLocationError(location, uniformName);
    glUniform1fv(location, 1, &value[0]);
}

void Shader::SetVec2(const std::string& uniformName, const glm::vec2& value) const {
    GLint location = glGetUniformLocation(m_program, uniformName.c_str());
    CheckLocationError(location, uniformName);
    glUniform2fv(location, 1, &value[0]);
}

void Shader::SetVec3(const std::string& uniformName, const glm::vec3& value) const {
    GLint location = glGetUniformLocation(m_program, uniformName.c_str());
    CheckLocationError(location, uniformName);
    glUniform3fv(location, 1, &value[0]);
}

void Shader::SetVec4(const std::string& uniformName, const glm::vec4& value) const {
    GLint location = glGetUniformLocation(m_program, uniformName.c_str());
    CheckLocationError(location, uniformName);
    glUniform4fv(location, 1, &value[0]);
}

void Shader::SetMat2(const std::string& uniformName, const glm::mat2& value) const {
    GLint location = glGetUniformLocation(m_program, uniformName.c_str());
    CheckLocationError(location, uniformName);
    glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetMat3(const std::string& uniformName, const glm::mat3& value) const {
    GLint location = glGetUniformLocation(m_program, uniformName.c_str());
    CheckLocationError(location, uniformName);
    glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetMat4(const std::string& uniformName, const glm::mat4& value) const {
    GLint location = glGetUniformLocation(m_program, uniformName.c_str());
    CheckLocationError(location, uniformName);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::Processing() {
    const ScreenSize& screen = Everywhere::Instance().Get<Window>().GetScreen();

    const glm::mat4 VIEW_DUMMY = glm::translate(Space::MODEL, glm::vec3(.0f, .0f, -2.f));
    const glm::mat4 PROJECTION_DUMMY =
            glm::perspective(glm::radians(85.0f),
                             static_cast<GLfloat>(screen.GetWidth()) /
                             static_cast<GLfloat>(screen.GetHeight()),
                             .1f, 2000.f);

    Use();

    SetMat4("mvp.model", Space::MODEL);
    SetMat4("mvp.view", VIEW_DUMMY);
    SetMat4("mvp.projection", PROJECTION_DUMMY);

    SetMat4("transform", GetGlobalTransform().ToMatrix());

    m_uniformProcessingFunc(this);
}
