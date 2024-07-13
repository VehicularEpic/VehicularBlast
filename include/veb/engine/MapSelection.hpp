#pragma once

#include "veb/engine/Entity.hpp"
#include "veb/engine/Map.hpp"
#include "veb/engine/Game.hpp"
#include "veb/engine/World.hpp"
#include "veb/render/WorldRenderer.hpp"

namespace veb {
namespace state {

class MapSelection {
private:
    Game &game;
    std::vector<Map>::const_iterator map_it;

    Camera camera;
    WorldRenderer renderer;
    World world;

    void UpdateMap();

public:
    MapSelection(Game &game);
    ~MapSelection() = default;

    void Run(double delta);
};

} // namespace state
} // namespace veb
