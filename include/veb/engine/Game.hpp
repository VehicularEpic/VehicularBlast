#pragma once

#include "veb/engine/EntityRenderer.hpp"
#include "veb/engine/Map.hpp"
#include "veb/engine/SkyboxRenderer.hpp"
#include "veb/engine/State.hpp"
#include "veb/gui/Window.hpp"
#include "veb/io/Keyboard.hpp"
#include "veb/io/MeshBank.hpp"

#include <memory>
#include <stack>
#include <vector>

namespace veb {

class Game {
private:
    Window window;
    Keyboard keyboard;
    MeshBank meshBank;
    EntityRenderer entityRenderer;
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

    const EntityRenderer &GetEntityRenderer() const {
        return entityRenderer;
    }

    const SkyboxRenderer &GetSkyboxRenderer() const {
        return skyboxRenderer;
    }

    void PushState(std::unique_ptr<State> state) {
        states.push(std::move(state));
    }

    void PopState() {
        states.pop();
    }

    void Start() const;
};

} // namespace veb
