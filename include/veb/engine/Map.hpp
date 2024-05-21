#pragma once

#include <string>
#include <vector>

#include <glm/vec3.hpp>

namespace veb {

struct MapObject {
    std::string name;
    glm::vec3 position;
    glm::vec3 rotation;
};

class Map {
private:
    std::string name;
    glm::vec3 ambient = {1.f, 1.f, 1.f};
    glm::vec3 sky = {0.f, 0.f, 0.f};
    glm::vec3 ground = {.5f, .5f, .5f};

    std::vector<MapObject> objects;

public:
    Map(const std::string &filePath);
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

    std::vector<MapObject> GetObjects() const {
        return objects;
    }
};

} // namespace veb
