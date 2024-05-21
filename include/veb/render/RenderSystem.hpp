#pragma once

#include "veb/gfx/ShaderProgram.hpp"
#include "veb/engine/Entity.hpp"

#include <vector>

namespace veb {

class RenderSystem {
private:
    ShaderProgram shader;

public:
    RenderSystem();
    ~RenderSystem() = default;

    void SetAmbientColor(glm::vec3 color) const {
        shader.Vec3("ambient", color);
    }

    void SetLightPosition(glm::vec3 position) const {
        shader.Vec3("u_LightPos", position);
    }

    void SetViewMatrix(glm::mat4 matrix) const {
        shader.Matrix4x4f("view", matrix);
    }

    void SetProjectionMatrix(glm::mat4 matrix) const {
        shader.Matrix4x4f("projection", matrix);
    }

    void Render(const Entity &entity) const;
    void Render(const std::vector<Entity> &entities) const;
};

} // namespace veb
