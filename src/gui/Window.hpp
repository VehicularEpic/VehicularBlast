#pragma once

#include <functional>
#include <string>
#include <vector>

namespace veb {

class Window {
public:
    using FramebufferSizeCallbackFn = std::function<void(int, int)>;

private:
    void *handle;

    std::vector<FramebufferSizeCallbackFn> framebufferSizeListeners;

    template<typename T>
    static void FramebufferSizeCallback(T *window, int w, int h);

public:
    Window(const std::string &name);
    ~Window();

    int GetWidth() const;
    void SetWidth(int width);

    int GetHeight() const;
    void SetHeight(int height);

    bool IsActive() const;
    double GetTime() const;

    void Clear() const;
    void Update() const;

    void AddFramebufferSizeCallback(const FramebufferSizeCallbackFn &callback) {
        framebufferSizeListeners.push_back(callback);
    }
};

} // namespace veb
