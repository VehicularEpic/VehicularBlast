#pragma once

#include "veb/gfx/ShaderProgram.hpp"
#include "veb/engine/Entity.hpp"
#include "veb/engine/Camera.hpp"
#include "veb/engine/World.hpp"

#include <vector>

namespace veb {

class WorldRenderer {
private:
    const ShaderProgram &entity;
    const ShaderProgram &sky;

public:
    WorldRenderer();
    ~WorldRenderer() = default;

    void SetAmbientLight(glm::vec3 position, glm::vec3 color) const {
        entity.Vec3("u_LightPos", position);
        entity.Vec3("ambient", color);
        sky.Vec3("ambient", color);
    }

    void SetCamera(const Camera &camera) const {
        auto matrix = camera.GetMatrix();
        entity.Matrix4x4f("view", matrix);
        sky.Matrix4x4f("view", matrix);
    }

    void SetProjectionMatrix(glm::mat4 matrix) const {
        entity.Matrix4x4f("projection", matrix);
        sky.Matrix4x4f("projection", matrix);
    }

    void SetSkyColor(glm::vec3 color) {
        sky.Vec3("skyColor", color);
    }

    void SetGroundColor(glm::vec3 color) {
        sky.Vec3("groundColor", color);
    }

    void Render(const World &world) const;
};

} // namespace veb
