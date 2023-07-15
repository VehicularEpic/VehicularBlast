#pragma once

#include "veb/gfx/Mesh.hpp"

#include <map>
#include <string>

namespace veb {

class MeshBank {
private:
    const std::string baseDir;
    std::map<std::string, Mesh> meshes;

public:
    MeshBank(std::string baseDir);
    ~MeshBank() = default;

    void Load(const std::string &name);
    const Mesh &GetMesh(const std::string &name) const;
};

} // namespace veb
