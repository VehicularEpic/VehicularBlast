#pragma once

#include <cstdint>

#include "../io/MeshFile.hpp"

namespace veb {

class Mesh {
private:
    uint32_t object = 0;
    uint32_t count = 0;

public:
    Mesh(const MeshFile &file);
    ~Mesh();

    Mesh(const Mesh &mesh) = delete;
    Mesh(Mesh &&mesh) noexcept;

    void Render();
};

} // namespace veb
