#include "veb/engine/VehicleSelection.hpp"

#include "veb/component/Components.hpp"
#include "veb/component/ComponentMesh.hpp"
#include "veb/component/ComponentPosition.hpp"
#include "veb/component/ComponentRotation.hpp"
#include "veb/engine/MapSelection.hpp"
#include "veb/engine/StateManager.hpp"

namespace veb {
namespace state {

VehicleSelection::VehicleSelection(Game &g) : game(g) {
    camera.SetPosition(0.f, 4.f, -15.f);
    camera.SetTarget(0.f, 0.f, 0.f);

    renderer.SetCamera(camera);
    renderer.SetAmbientLight({0.f, 100.f, 0.f}, {1.f, 1.f, 1.f});

    Components<ComponentMesh>::Put(entity, {g.GetMeshBank().GetMesh("destroy")});
    Components<ComponentPosition>::Put(entity, {});
    Components<ComponentRotation>::Put(entity, {});
    world.AddEntity(entity);
}

void VehicleSelection::Run(double delta) {
    auto &keyboard = game.GetKeyboard();

    if (keyboard.Poll(VK_ENTER)) {
        StateManager::Replace<MapSelection>(game);
        return;
    }

    auto &rotation = Components<ComponentRotation>::Get(entity);
    rotation.yaw += delta;

    renderer.Render(world);
}

} // namespace state
} // namespace veb
