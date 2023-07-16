#include "veb/engine/Game.hpp"
#include "veb/engine/MainMenu.hpp"

int main(int argc, char const *argv[]) {
    veb::Game game;
    game.PushState(std::make_unique<veb::state::MainMenu>(game));
    game.Start();

    return 0;
}
