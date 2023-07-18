#pragma once

#include "veb/engine/Entity.hpp"
#include "veb/engine/Game.hpp"

#include <vector>

namespace veb {

class World {
private:
    const Game &game;
    std::vector<Entity> entities;

public:
    World(const Game &game);
    ~World() = default;

    void Render() const;

    void AddEntity(Entity entity) {
        entities.push_back(entity);
    }

    void Clear() {
        entities.clear();
    }
};

} // namespace veb
