#include "veb/gfx/ShaderProgram.hpp"

#include <iostream>

#include <glad/gl.h>
#include <glm/gtc/type_ptr.hpp>

namespace veb {

ShaderProgram::ShaderProgram() {
    program = glCreateProgram();
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(program);
}

ShaderProgram::ShaderProgram(ShaderProgram &&s) noexcept
    : program(s.program) {
    s.program = 0;
}

void ShaderProgram::Bind() const {
    glUseProgram(program);
}

void ShaderProgram::Unbind() const {
    glUseProgram(0);
}

bool ShaderProgram::Link() {
    glLinkProgram(program);

    GLint success = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success) {
        GLint length = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

        GLchar *info = (GLchar *) malloc(length * sizeof(GLchar));
        glGetProgramInfoLog(program, length, nullptr, info);

        std::cerr << "LiteGraphics Error: Shader linking error\n"
                  << info << std::endl;

        free(info);
        return GL_FALSE;
    }

    return GL_TRUE;
}

template<ShaderType _Type>
void ShaderProgram::Attach(const Shader<_Type> &shader) {
    shader.Attach(program);
}

template<ShaderType _Type>
void ShaderProgram::Detach(const Shader<_Type> &shader) {
    shader.Detach(program);
}

void ShaderProgram::Vec3(std::string uniform, const glm::vec3 &vector) const {
    GLuint location = glGetUniformLocation(program, uniform.c_str());
    glUniform3fv(location, 1, glm::value_ptr(vector));
}

void ShaderProgram::Matrix4x4f(std::string uniform, const glm::mat4 &matrix) const {
    GLuint location = glGetUniformLocation(program, uniform.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

template void ShaderProgram::Attach(const Shader<ShaderType::Vertex> &shader);
template void ShaderProgram::Attach(const Shader<ShaderType::Fragment> &shader);

template void ShaderProgram::Detach(const Shader<ShaderType::Vertex> &shader);
template void ShaderProgram::Detach(const Shader<ShaderType::Fragment> &shader);

} // namespace veb
