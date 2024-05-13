#pragma once

#include "veb/engine/Map.hpp"
#include "veb/engine/SkyboxRenderer.hpp"
#include "veb/engine/State.hpp"
#include "veb/gui/Window.hpp"
#include "veb/io/Keyboard.hpp"
#include "veb/io/MeshBank.hpp"
#include "veb/render/RenderSystem.hpp"

#include <memory>
#include <stack>
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
    std::stack<std::unique_ptr<State>> states;

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

    void PushState(std::unique_ptr<State> state) {
        states.push(std::move(state));
    }

    std::unique_ptr<State> PopState() {
        auto state = std::move(states.top());
        states.pop();
        return state;
    }

    void Start() const;
};

} // namespace veb
