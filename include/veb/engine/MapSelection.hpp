#pragma once

#include "veb/engine/Entity.hpp"
#include "veb/engine/Map.hpp"
#include "veb/engine/Game.hpp"
#include "veb/engine/State.hpp"

#include <glm/mat4x4.hpp>

namespace veb {
namespace state {

class MapSelection : public virtual State {
private:
    Game &game;
    Entity player;
    std::vector<Map>::const_iterator map_it;

    glm::mat4 view;
    std::vector<Entity> entities;

    void UpdateMap();

public:
    MapSelection(Game &game, Entity player);
    ~MapSelection() = default;

    void Run(double delta);
};

} // namespace state
} // namespace veb
