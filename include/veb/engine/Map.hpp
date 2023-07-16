#pragma once

#include "veb/engine/Entity.hpp"
#include "veb/io/MeshBank.hpp"

#include <string>

#include <glm/vec3.hpp>

namespace veb {

class Map {
private:
    std::string name;
    glm::vec3 ambient = {1.f, 1.f, 1.f};
    glm::vec3 sky = {0.f, 0.f, 0.f};
    glm::vec3 ground = {.5f, .5f, .5f};

    std::vector<Entity> entities;

public:
    Map(const std::string &filePath, const MeshBank &bank);
    ~Map() = default;

    std::string GetName() const {
        return name;
    }

    glm::vec3 GetAmbientColor() const {
        return ambient;
    }

    glm::vec3 GetSkyColor() const {
        return sky;
    }

    glm::vec3 GetGroundColor() const {
        return ground;
    }

    std::vector<Entity> GetEntities() const {
        return entities;
    }
};

} // namespace veb
