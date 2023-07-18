#include "veb/engine/World.hpp"

#include "veb/gfx/Rect.hpp"

namespace veb {

World::World(const Game &game) : game(game) {
}

void World::Render() const {
    auto &skyboxRenderer = game.GetSkyboxRenderer();
    skyboxRenderer.Bind();

    auto &skybox = Rect::GetInstance();
    skybox.Render();

    auto &entityRenderer = game.GetEntityRenderer();
    for (auto &entity : entities) {
        entityRenderer.SetModelMatrix(entity.GetModelMatrix());
        entity.Render();
    }
}

} // namespace veb
