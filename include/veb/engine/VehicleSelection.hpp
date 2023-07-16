#pragma once

#include "veb/engine/Entity.hpp"
#include "veb/engine/Game.hpp"
#include "veb/engine/State.hpp"

#include <glm/mat4x4.hpp>

namespace veb {
namespace state {

class VehicleSelection : public virtual State {
private:
    Game &game;
    Entity entity;

    glm::mat4 view;

public:
    VehicleSelection(Game &game);
    ~VehicleSelection() = default;

    void Run(double delta);
};

} // namespace state
} // namespace veb
