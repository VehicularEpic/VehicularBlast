#pragma once

#include "veb/engine/Game.hpp"
#include "veb/engine/State.hpp"

namespace veb {
namespace state {

class MainMenu : public virtual State {
private:
    Game &game;

public:
    MainMenu(Game &game);
    ~MainMenu() = default;

    void Run(double delta);
};

} // namespace state
} // namespace veb
