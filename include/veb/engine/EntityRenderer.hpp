#pragma once

#include "veb/gfx/ShaderProgram.hpp"

namespace veb {

class EntityRenderer : private virtual ShaderProgram {
public:
    EntityRenderer();

    void SetProjectionMatrix(glm::mat4 matrix) const {
        Matrix4x4f("projection", matrix);
    }

    void SetViewMatrix(glm::mat4 matrix) const {
        Matrix4x4f("view", matrix);
    }

    void SetModelMatrix(glm::mat4 matrix) const {
        Matrix4x4f("model", matrix);
    }

    void SetAmbientColor(glm::vec3 color) const {
        Vec3("ambient", color);
    }

    void SetLightPosition(glm::vec3 position) const {
        Vec3("u_LightPos", position);
    }
};

} // namespace veb
