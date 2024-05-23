#include "veb/engine/Game.hpp"
#include "veb/engine/MainMenu.hpp"
#include "veb/engine/StateManager.hpp"

int main(int argc, char const *argv[]) {
    veb::Game game;
    veb::StateManager::Push<veb::state::MainMenu>(game);
    game.Start();

    return 0;
}
