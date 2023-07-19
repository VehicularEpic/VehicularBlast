#pragma once

#include "veb/gfx/ShaderProgram.hpp"

namespace veb {

class SkyboxRenderer : private virtual ShaderProgram {
public:
    using ShaderProgram::Bind;

    SkyboxRenderer();

    void SetProjectionMatrix(glm::mat4 matrix) const {
        Matrix4x4f("projection", matrix);
    }

    void SetViewMatrix(glm::mat4 matrix) const {
        Matrix4x4f("view", matrix);
    }

    void SetAmbientColor(glm::vec3 color) const {
        Vec3("ambient", color);
    }

    void SetSkyColor(glm::vec3 color) const {
        Vec3("skyColor", color);
    }

    void SetGroundColor(glm::vec3 color) const {
        Vec3("groundColor", color);
    }
};

} // namespace veb
