#include "veb/engine/VehicleSelection.hpp"

#include "veb/engine/MapSelection.hpp"

#include <glm/ext/matrix_transform.hpp>

namespace veb {
namespace state {

VehicleSelection::VehicleSelection(Game &g) : game(g), entity(g.GetMeshBank().GetMesh("destroy")), renderer(g.GetEntityRenderer()) {
    view = glm::lookAt(glm::vec3(0.f, 4.f, -15.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 1.f));

    renderer.SetViewMatrix(view);
    renderer.SetAmbientColor(glm::vec3(1.f, 1.f, 1.f));
    renderer.SetLightPosition(glm::vec3(0.f, 100.f, 0.f));
}

void VehicleSelection::Run(double delta) {
    auto &keyboard = game.GetKeyboard();

    if (keyboard.Poll(VK_ENTER)) {
        auto state = game.PopState();
        game.PushState(std::make_unique<MapSelection>(game, entity));
        return;
    }

    entity.Rotate(0.f, (float) delta, 0.f);

    renderer.SetModelMatrix(entity.GetModelMatrix());
    entity.Render();
}

} // namespace state
} // namespace veb
