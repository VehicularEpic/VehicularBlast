#pragma once

#include "veb/engine/Entity.hpp"
#include "veb/engine/Game.hpp"
#include "veb/engine/World.hpp"
#include "veb/render/WorldRenderer.hpp"

namespace veb {
namespace state {

class VehicleSelection {
private:
    Game &game;
    Entity entity;
    Camera camera;

    World world;
    WorldRenderer renderer;

public:
    VehicleSelection(Game &game);
    ~VehicleSelection() = default;

    void Run(double delta);
};

} // namespace state
} // namespace veb
