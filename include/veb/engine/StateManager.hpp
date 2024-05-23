#pragma once

#include <functional>
#include <memory>
#include <stack>

namespace veb {

class StateManager final {
private:
    StateManager() = delete;
    ~StateManager() = delete;

    StateManager(const StateManager &) = delete;
    StateManager(StateManager &&) = delete;

    StateManager &operator=(const StateManager &) = delete;
    StateManager &operator=(StateManager &&) = delete;

    static std::stack<std::function<void(double)>> &stack() {
        static std::stack<std::function<void(double)>> states;
        return states;
    }

public:
    template<class T, class... U>
    static void Push(U &&...args) {
        auto instance = std::make_shared<T>(std::forward<U>(args)...);
        auto state = [instance](double delta) { instance->Run(delta); };
        stack().push(state);
    }

    template<class T, class... U>
    static void Replace(U &&...args) {
        Pop();
        Push<T>(std::forward<U>(args)...);
    }

    static void Pop() {
        stack().pop();
    }

    static void Update(double delta) {
        stack().top()(delta);
    }
};

} // namespace veb
