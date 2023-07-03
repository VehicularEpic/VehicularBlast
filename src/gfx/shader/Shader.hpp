#pragma once

#include <cstdint>
#include <string>

namespace veb {

enum ShaderType : uint32_t {
    Vertex = 0,
    Fragment = 1,
};

template<ShaderType _Ty>
class Shader {

private:
    uint32_t shader = 0;

public:
    Shader(std::string source);
    ~Shader();

    Shader(const Shader &s) = delete;
    Shader(Shader &&s) noexcept;

    void Attach(uint32_t program) const;
    void Detach(uint32_t program) const;
};

} // namespace veb
