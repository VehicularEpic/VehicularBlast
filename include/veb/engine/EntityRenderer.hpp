#pragma once

#include "veb/gfx/ShaderProgram.hpp"

namespace veb {

class EntityRenderer {
private:
    ShaderProgram shader;

public:
    EntityRenderer();
    ~EntityRenderer() = default;

    EntityRenderer(const EntityRenderer &e) = delete;
    EntityRenderer(EntityRenderer &&e) noexcept;

    void Begin() const {
        shader.Bind();
    }

    void End() const {
        shader.Unbind();
    }

    void SetProjectionMatrix(glm::mat4 matrix) const {
        shader.Matrix4x4f("projection", matrix);
    }

    void SetViewMatrix(glm::mat4 matrix) const {
        shader.Matrix4x4f("view", matrix);
    }

    void SetModelMatrix(glm::mat4 matrix) const {
        shader.Matrix4x4f("model", matrix);
    }

    void SetAmbientColor(glm::vec3 color) const {
        shader.Vec3("ambient", color);
    }

    void SetLightPosition(glm::vec3 position) const {
        shader.Vec3("u_LightPos", position);
    }
};

} // namespace veb
