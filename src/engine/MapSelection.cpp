#include "veb/engine/MapSelection.hpp"

#include <glm/ext/matrix_transform.hpp>

namespace veb {
namespace state {

MapSelection::MapSelection(Game &g, Entity p) : game(g), player(p), map_it(g.GetMaps().begin()), world(g) {
    view = glm::lookAt(glm::vec3(0.f, 20.f, -100.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 1.f));

    player.SetPosition(0.f, 0.f, 0.f);
    player.SetRotation(0.f, 0.f, 0.f);

    UpdateMap();
}

void MapSelection::UpdateMap() {
    auto &entityRenderer = game.GetEntityRenderer();
    entityRenderer.SetAmbientColor(map_it->GetAmbientColor());
    entityRenderer.SetLightPosition(glm::vec3(0.f, 100.f, 40.f));

    auto &skyboxRenderer = game.GetSkyboxRenderer();
    skyboxRenderer.SetAmbientColor(map_it->GetAmbientColor());
    skyboxRenderer.SetSkyColor(map_it->GetSkyColor());
    skyboxRenderer.SetGroundColor(map_it->GetGroundColor());

    world.Clear();
    world.AddEntity(player);

    for (veb::Entity entity : map_it->GetEntities())
        world.AddEntity(entity);
}

void MapSelection::Run(double delta) {
    auto &keyboard = game.GetKeyboard();

    if (keyboard.Poll(VK_RIGHT)) {
        ++map_it;

        if (map_it == game.GetMaps().end())
            map_it = game.GetMaps().begin();

        UpdateMap();
    }

    if (keyboard.Poll(VK_LEFT)) {
        if (map_it == game.GetMaps().begin())
            map_it = game.GetMaps().end();

        --map_it;

        UpdateMap();
    }

    view = glm::rotate(view, (float) delta, glm::vec3(0.f, -1.f, 0.f));

    auto &entityRenderer = game.GetEntityRenderer();
    entityRenderer.SetViewMatrix(view);

    auto &skyboxRenderer = game.GetSkyboxRenderer();
    skyboxRenderer.SetViewMatrix(view);

    world.Render();
}

} // namespace state
} // namespace veb
