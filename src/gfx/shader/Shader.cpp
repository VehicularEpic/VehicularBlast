#include "Shader.hpp"

#include <cstring>
#include <iostream>

#include <glad/gl.h>

static GLboolean CompileShader(GLuint shader) {
    glCompileShader(shader);

    GLint success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        GLint length = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

        GLchar *info = (GLchar *) malloc(length * sizeof(GLchar));
        glGetShaderInfoLog(shader, length, nullptr, info);

        std::cerr << "Error: Shader compilation error\n"
                  << info << std::endl;

        free(info);
        return GL_FALSE;
    }

    return GL_TRUE;
}

static GLenum GetGLShaderType(veb::ShaderType type) {
    switch (type) {
        case veb::ShaderType::Vertex:
            return GL_VERTEX_SHADER;
        case veb::ShaderType::Fragment:
            return GL_FRAGMENT_SHADER;
    }

    return GL_ARRAY_BUFFER;
}

namespace veb {

template<ShaderType _Ty>
Shader<_Ty>::Shader(std::string source) {
    shader = glCreateShader(GetGLShaderType(_Ty));

    const char *data = source.c_str();
    const GLint length = source.length();
    glShaderSource(shader, 1, &data, &length);

    if (!CompileShader(shader)) {
        glDeleteShader(shader);
        shader = 0;
    }
}

template<ShaderType _Ty>
Shader<_Ty>::~Shader() {
    glDeleteShader(shader);
}

template<ShaderType _Ty>
Shader<_Ty>::Shader(Shader<_Ty> &&s) noexcept
    : shader(s.shader) {
    s.shader = 0;
}

template<ShaderType _Ty>
void Shader<_Ty>::Attach(uint32_t program) const {
    glAttachShader(program, shader);
}

template<ShaderType _Ty>
void Shader<_Ty>::Detach(uint32_t program) const {
    glDetachShader(program, shader);
}

template class Shader<ShaderType::Vertex>;
template class Shader<ShaderType::Fragment>;

} // namespace veb
