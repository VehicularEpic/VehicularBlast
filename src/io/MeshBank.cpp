#include "MeshBank.hpp"

#include "../io/MeshFile.hpp"

#include <memory>

namespace veb {

MeshBank::MeshBank(std::string baseDir) : baseDir(baseDir) {}

void MeshBank::Load(const std::string &name) {
    veb::MeshFile file(baseDir + "/" + name + ".glb");
    veb::Mesh mesh(file);

    meshes.emplace(std::make_pair(name, std::move(mesh)));
}

const Mesh &MeshBank::GetMesh(const std::string &name) const {
    return meshes.at(name);
}

} // namespace veb
