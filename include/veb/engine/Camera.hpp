#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace veb {

class Camera {
private:
    glm::vec3 position;
    glm::vec3 target;

public:
    Camera() = default;
    ~Camera() = default;

    void SetPosition(float x, float y, float z);
    void SetTarget(float x, float y, float z);
    void Rotate(float x, float y, float z);

    glm::mat4 GetMatrix() const;
};

} // namespace veb
