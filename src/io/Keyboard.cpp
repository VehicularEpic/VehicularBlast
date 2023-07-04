#include "Keyboard.hpp"

#include <iostream>

namespace veb {

Keyboard::Keyboard(Window &window) {
    window.AddKeyCallback([&](int key, bool down) {
        KeyCallback(static_cast<Key>(key), down);
    });
}

void Keyboard::KeyCallback(Key key, bool down) {
    keys[key] = down;
}

bool Keyboard::IsPressed(Key key) {
    auto state = keys.find(key);
    return state != keys.end() && state->second;
}

} // namespace veb
