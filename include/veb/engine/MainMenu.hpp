#pragma once

#include "veb/engine/Game.hpp"

namespace veb {
namespace state {

class MainMenu {
private:
    Game &game;

public:
    MainMenu(Game &game);
    ~MainMenu() = default;

    void Run(double delta);
};

} // namespace state
} // namespace veb
