#include "veb/engine/MainMenu.hpp"

#include "veb/engine/StateManager.hpp"
#include "veb/engine/VehicleSelection.hpp"

namespace veb {
namespace state {

MainMenu::MainMenu(Game &g) : game(g) {
}

void MainMenu::Run(double delta) {
    auto &keyboard = game.GetKeyboard();

    if (keyboard.Poll(VK_ENTER)) {
        StateManager::Replace<VehicleSelection>(game);
    }
}

} // namespace state
} // namespace veb
