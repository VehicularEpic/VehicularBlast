#pragma once

#include <functional>
#include <string>
#include <vector>

namespace veb {

class Window {
public:
    using FramebufferSizeCallbackFn = std::function<void(int, int)>;

    using KeyCallbackFn = std::function<void(int, bool)>;

private:
    uint32_t width = 800;
    uint32_t height = 600;

    void *handle;

    std::vector<FramebufferSizeCallbackFn> framebufferSizeListeners;
    std::vector<KeyCallbackFn> keyListeners;

    template<typename T>
    static void FramebufferSizeCallback(T *window, int w, int h);

    template<typename T>
    static void WindowSizeCallback(T *window, int w, int h);

    template<typename T>
    static void KeyCallback(T *window, int key, int scancode, int action, int mods);

public:
    Window(const std::string &name);
    ~Window();

    int GetWidth() const {
        return width;
    }

    int GetHeight() const {
        return height;
    }

    void SetWidth(int width);
    void SetHeight(int height);

    bool IsActive() const;
    double GetTime() const;

    void Clear() const;
    void Update() const;

    void AddFramebufferSizeCallback(const FramebufferSizeCallbackFn &callback) {
        framebufferSizeListeners.push_back(callback);
    }

    void AddKeyCallback(const KeyCallbackFn &callback) {
        keyListeners.push_back(callback);
    }
};

} // namespace veb
