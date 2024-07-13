#pragma once

#include "veb/engine/Map.hpp"
#include "veb/gui/Window.hpp"
#include "veb/io/Keyboard.hpp"
#include "veb/io/MeshBank.hpp"

#include <vector>

namespace veb {

class Game {
private:
    Window window;
    Keyboard keyboard;
    MeshBank meshBank;

    std::vector<Map> maps;

public:
    Game();
    ~Game() = default;

    Keyboard &GetKeyboard() {
        return keyboard;
    }

    const MeshBank &GetMeshBank() const {
        return meshBank;
    }

    const std::vector<Map> &GetMaps() const {
        return maps;
    }

    void Start() const;
};

} // namespace veb
