#pragma once

#include "veb/gui/Window.hpp"

#include <cstdint>
#include <map>

namespace veb {

enum Key : uint16_t {
    VK_UNKNOWN = 0,

    VK_SPACE = 32,
    VK_0 = 48,
    VK_1 = 49,
    VK_2 = 50,
    VK_3 = 51,
    VK_4 = 52,
    VK_5 = 53,
    VK_6 = 54,
    VK_7 = 55,
    VK_8 = 56,
    VK_9 = 57,
    VK_A = 65,
    VK_B = 66,
    VK_C = 67,
    VK_D = 68,
    VK_E = 69,
    VK_F = 70,
    VK_G = 71,
    VK_H = 72,
    VK_I = 73,
    VK_J = 74,
    VK_K = 75,
    VK_L = 76,
    VK_M = 77,
    VK_N = 78,
    VK_O = 79,
    VK_P = 80,
    VK_Q = 81,
    VK_R = 82,
    VK_S = 83,
    VK_T = 84,
    VK_U = 85,
    VK_V = 86,
    VK_W = 87,
    VK_X = 88,
    VK_Y = 89,
    VK_Z = 90,

    VK_ESCAPE = 256,
    VK_ENTER = 257,
    VK_TAB = 258,
    VK_BACKSPACE = 259,
    VK_INSERT = 260,
    VK_DELETE = 261,
    VK_RIGHT = 262,
    VK_LEFT = 263,
    VK_DOWN = 264,
    VK_UP = 265,
    VK_PAGE_UP = 266,
    VK_PAGE_DOWN = 267,
    VK_HOME = 268,
    VK_END = 269,
    VK_F1 = 290,
    VK_F2 = 291,
    VK_F3 = 292,
    VK_F4 = 293,
    VK_F5 = 294,
    VK_F6 = 295,
    VK_F7 = 296,
    VK_F8 = 297,
    VK_F9 = 298,
    VK_F10 = 299,
    VK_F11 = 300,
    VK_F12 = 301,
};

class Keyboard {
private:
    std::map<Key, bool> keys;

    void KeyCallback(Key key, bool down);

public:
    Keyboard(Window &window);
    ~Keyboard() = default;

    bool IsPressed(Key key);
    bool Poll(Key key);
};

} // namespace veb
