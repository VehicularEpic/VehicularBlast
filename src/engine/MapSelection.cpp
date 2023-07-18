#include "veb/engine/MapSelection.hpp"

#include <glm/ext/matrix_transform.hpp>

namespace veb {
namespace state {

MapSelection::MapSelection(Game &g, Entity p) : game(g), player(p), renderer(g.GetEntityRenderer()), map_it(g.GetMaps().begin()) {
    view = glm::lookAt(glm::vec3(0.f, 100.f, -30.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, -1.f, 0.f));

    player.SetPosition(0.f, 0.f, 0.f);
    player.SetRotation(0.f, 0.f, 0.f);

    UpdateMap();
}

void MapSelection::UpdateMap() {
    renderer.SetAmbientColor(map_it->GetAmbientColor());
    renderer.SetLightPosition(glm::vec3(0.f, 100.f, -100.f));

    entities.clear();
    for (veb::Entity entity : map_it->GetEntities())
        entities.push_back(entity);
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

    view = glm::rotate(view, (float) delta, glm::vec3(0.f, 0.f, -1.f));
    renderer.SetViewMatrix(view);

    renderer.SetModelMatrix(player.GetModelMatrix());
    player.Render();

    for (const veb::Entity &entity : entities) {
        renderer.SetModelMatrix(entity.GetModelMatrix());
        entity.Render();
    }
}

} // namespace state
} // namespace veb
