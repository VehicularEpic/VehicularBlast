#pragma once

#include "veb/engine/Entity.hpp"
#include "veb/io/MeshBank.hpp"

#include <string>

namespace veb {

class Map {
private:
    std::string name;
    std::vector<Entity> entities;

public:
    Map(const std::string &filePath, const MeshBank &bank);
    ~Map() = default;

    std::string GetName() const {
        return name;
    }

    std::vector<Entity> GetEntities() const {
        return entities;
    }
};

} // namespace veb
