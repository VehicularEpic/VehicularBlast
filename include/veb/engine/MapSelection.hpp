#pragma once

#include "veb/engine/Entity.hpp"
#include "veb/engine/EntityRenderer.hpp"
#include "veb/engine/Map.hpp"
#include "veb/engine/Game.hpp"
#include "veb/engine/State.hpp"
#include "veb/engine/World.hpp"

#include <glm/mat4x4.hpp>

namespace veb {
namespace state {

class MapSelection : public virtual State {
private:
    Game &game;
    Entity player;
    std::vector<Map>::const_iterator map_it;

    World world;
    glm::mat4 view;

    void UpdateMap();

public:
    MapSelection(Game &game, Entity player);
    ~MapSelection() = default;

    void Run(double delta);
};

} // namespace state
} // namespace veb
