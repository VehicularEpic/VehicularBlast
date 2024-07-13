#include "veb/engine/Camera.hpp"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

namespace veb {

void Camera::SetPosition(float x, float y, float z) {
    position = glm::vec3(x, y, z);
}

void Camera::SetTarget(float x, float y, float z) {
    target = glm::vec3(x, y, z);
}

void Camera::Rotate(float x, float y, float z) {
    position = glm::rotate(position, x, glm::vec3(1.f, 0.f, 0.f));
    position = glm::rotate(position, y, glm::vec3(0.f, 1.f, 0.f));
    position = glm::rotate(position, z, glm::vec3(0.f, 0.f, 1.f));
}

glm::mat4 Camera::GetMatrix() const {
    return glm::lookAt(position, target, glm::vec3(0.f, 1.f, 0.f));
}

} // namespace veb
