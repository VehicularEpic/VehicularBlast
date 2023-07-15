#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace veb {

class MeshFile {
private:
    uint32_t points = 0;
    std::vector<float> data;

public:
    MeshFile(const std::string &filePath);
    ~MeshFile() = default;

    uint32_t GetTotalPoints() const {
        return points;
    }

    const std::vector<float> &GetData() const {
        return data;
    }
};

} // namespace veb
