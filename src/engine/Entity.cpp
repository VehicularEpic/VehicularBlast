#include "veb/engine/Entity.hpp"

#include <glm/vec3.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace veb {

glm::mat4 Entity::GetModelMatrix() const {
    glm::mat4 matrix = glm::identity<glm::mat4>();
    matrix = glm::translate(matrix, glm::vec3(x, -z, -y));

    // https://en.wikipedia.org/wiki/Aircraft_principal_axes
    matrix = matrix * glm::toMat4(glm::quat(glm::cos(pitch / 2.f), glm::sin(pitch / 2.f), 0.f, 0.f));
    matrix = matrix * glm::toMat4(glm::quat(glm::cos(yaw / 2.f), 0.f, 0.f, glm::sin(yaw / 2.f)));
    matrix = matrix * glm::toMat4(glm::quat(glm::cos(roll / 2.f), 0.f, -glm::sin(roll / 2.f), 0.f));

    return matrix;
}

} // namespace veb
