#pragma once

#include "../gfx/Mesh.hpp"

#include <glm/mat4x4.hpp>

namespace veb {

class Entity {
private:
    const Mesh &mesh;

    float x = 0.f;
    float y = 0.f;
    float z = 0.f;

    float pitch = 0.f;
    float yaw = 0.f;
    float roll = 0.f;

public:
    Entity(const Mesh &mesh) : mesh(mesh) {}
    ~Entity() = default;

    void Render() const {
        mesh.Render();
    }

    void Move(float px, float py, float pz) {
        x += px;
        y += py;
        z += pz;
    }

    void SetPosition(float px, float py, float pz) {
        x = px;
        y = py;
        z = pz;
    }

    void SetX(float px) {
        x = px;
    }

    void SetY(float py) {
        y = py;
    }

    void SetZ(float pz) {
        z = pz;
    }

    void Rotate(float x, float y, float z) {
        pitch += x;
        yaw += y;
        roll += z;
    }

    void SetRotation(float x, float y, float z) {
        pitch = x;
        yaw = y;
        roll = z;
    }

    void SetPitch(float x) {
        pitch = x;
    }

    void SetYaw(float y) {
        yaw = y;
    }

    void SetRoll(float z) {
        roll = z;
    }

    glm::mat4 GetModelMatrix() const;
};

} // namespace veb
