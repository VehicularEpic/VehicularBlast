#pragma once

#include "Shader.hpp"

#include <cstdint>
#include <string>

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace veb {

class ShaderProgram {
private:
    uint32_t program = 0;

public:
    ShaderProgram();
    ~ShaderProgram();

    ShaderProgram(const ShaderProgram &s) = delete;
    ShaderProgram(ShaderProgram &&s) noexcept;

    void Bind() const;
    void Unbind() const;

    bool Link();

    template<ShaderType _Type>
    void Attach(const Shader<_Type> &shader);
    template<ShaderType _Type>
    void Detach(const Shader<_Type> &shader);

    void Vec3(std::string uniform, const glm::vec3 &vector) const;
    void Matrix4x4f(std::string uniform, const glm::mat4 &matrix) const;
};

} // namespace veb
