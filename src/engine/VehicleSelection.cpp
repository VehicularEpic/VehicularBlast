#include "veb/engine/VehicleSelection.hpp"

#include "veb/component/Components.hpp"
#include "veb/component/ComponentMesh.hpp"
#include "veb/component/ComponentPosition.hpp"
#include "veb/component/ComponentRotation.hpp"
#include "veb/engine/MapSelection.hpp"

#include <glm/ext/matrix_transform.hpp>

namespace veb {
namespace state {

VehicleSelection::VehicleSelection(Game &g) : game(g) {
    view = glm::lookAt(glm::vec3(0.f, 4.f, -15.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 1.f));

    Components<ComponentMesh>::Put(entity, ComponentMesh{g.GetMeshBank().GetMesh("destroy")});
    Components<ComponentPosition>::Put(entity, ComponentPosition{});
    Components<ComponentRotation>::Put(entity, ComponentRotation{});

    const RenderSystem &renderer = g.GetRenderSystem();
    renderer.SetViewMatrix(view);
    renderer.SetAmbientColor(glm::vec3(1.f, 1.f, 1.f));
    renderer.SetLightPosition(glm::vec3(0.f, 100.f, 0.f));
}

void VehicleSelection::Run(double delta) {
    auto &keyboard = game.GetKeyboard();

    if (keyboard.Poll(VK_ENTER)) {
        auto state = game.PopState();
        game.PushState(std::make_unique<MapSelection>(game));
        return;
    }

    auto &rotation = Components<ComponentRotation>::Get(entity);
    rotation.yaw += delta;

    const RenderSystem &renderer = game.GetRenderSystem();
    renderer.Render(entity);
}

} // namespace state
} // namespace veb
