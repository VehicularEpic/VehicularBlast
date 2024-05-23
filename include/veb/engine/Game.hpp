#pragma once

#include "veb/engine/Map.hpp"
#include "veb/engine/SkyboxRenderer.hpp"
#include "veb/gui/Window.hpp"
#include "veb/io/Keyboard.hpp"
#include "veb/io/MeshBank.hpp"
#include "veb/render/RenderSystem.hpp"

#include <vector>

namespace veb {

class Game {
private:
    Window window;
    Keyboard keyboard;
    MeshBank meshBank;
    RenderSystem renderSystem;
    SkyboxRenderer skyboxRenderer;

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

    const RenderSystem &GetRenderSystem() const {
        return renderSystem;
    }

    const SkyboxRenderer &GetSkyboxRenderer() const {
        return skyboxRenderer;
    }

    void Start() const;
};

} // namespace veb
