#pragma once

#include "veb/engine/Map.hpp"
#include "veb/engine/State.hpp"
#include "veb/gfx/ShaderProgram.hpp"
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
    ShaderProgram shader;

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

    void PushState(std::unique_ptr<State> state) {
        states.push(std::move(state));
    }

    void PopState() {
        states.pop();
    }

    void SetModelMatrix(glm::mat4 matrix) {
        shader.Matrix4x4f("model", matrix);
    }

    void SetViewMatrix(glm::mat4 matrix) {
        shader.Matrix4x4f("view", matrix);
    }

    void SetAmbientColor(glm::vec3 color) {
        shader.Vec3("ambient", color);
    }

    void Start() const;
};

} // namespace veb
