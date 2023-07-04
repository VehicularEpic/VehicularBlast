#pragma once

#include <cstdint>
#include <vector>

namespace veb {

class Mesh {
private:
    uint32_t object = 0;
    uint32_t count = 0;

public:
    Mesh(std::vector<float> data, uint32_t count);
    ~Mesh();

    Mesh(const Mesh &mesh) = delete;
    Mesh(Mesh &&mesh) noexcept;

    void Render() const;
};

} // namespace veb
