#include "veb/engine/World.hpp"

namespace veb {

World::World(const Game &game) : game(game) {
}

void World::Render() const {
    auto &entityRenderer = game.GetEntityRenderer();
    for (auto &entity : entities) {
        entityRenderer.SetModelMatrix(entity.GetModelMatrix());
        entity.Render();
    }
}

} // namespace veb
