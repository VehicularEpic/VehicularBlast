#include "veb/render/WorldRenderer.hpp"

#include "veb/component/Components.hpp"
#include "veb/component/ComponentMesh.hpp"
#include "veb/component/ComponentPosition.hpp"
#include "veb/component/ComponentRotation.hpp"
#include "veb/gfx/Rect.hpp"
#include "veb/gfx/ShaderProgram.hpp"
#include "veb/registry/Registry.hpp"

#include <glm/vec3.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace veb {

static glm::mat4 CreateEntityMatrix(ComponentPosition &position, ComponentRotation &rotation) {
    glm::mat4 matrix = glm::identity<glm::mat4>();
    matrix = glm::translate(matrix, glm::vec3(position.x, position.y, -position.z));

    // https://en.wikipedia.org/wiki/Aircraft_principal_axes
    matrix = matrix * glm::toMat4(glm::quat(glm::cos(rotation.pitch / 2.f), glm::sin(rotation.pitch / 2.f), 0.f, 0.f));
    matrix = matrix * glm::toMat4(glm::quat(glm::cos(rotation.yaw / 2.f), 0.f, -glm::sin(rotation.yaw / 2.f), 0.f));
    matrix = matrix * glm::toMat4(glm::quat(glm::cos(rotation.roll / 2.f), 0.f, 0.f, glm::sin(rotation.roll / 2.f)));

    return matrix;
}

WorldRenderer::WorldRenderer()
    : entity(Registry<ShaderProgram>::Fetch().Get("entity")),
      sky(Registry<ShaderProgram>::Fetch().Get("sky")) {
}

void WorldRenderer::Render(const World &world) const {
    sky.Bind();
    Rect::GetInstance().Render();

    world.Process([&](Entity e) {
        if (!Components<ComponentMesh>::Has(e) || !Components<ComponentPosition>::Has(e) || !Components<ComponentRotation>::Has(e))
            return;

        entity.Matrix4x4f("model", CreateEntityMatrix(Components<ComponentPosition>::Get(e), Components<ComponentRotation>::Get(e)));
        Components<ComponentMesh>::Get(e).mesh.Render();
    });
}

} // namespace veb
