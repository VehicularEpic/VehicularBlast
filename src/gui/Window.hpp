#pragma once

#include <string>

namespace veb {

    class Window {
    private:
        void *handle;

    public:
        Window(const std::string &name);
        ~Window();

        int GetWidth() const;
        void SetWidth(int width);

        int GetHeight() const;
        void SetHeight(int height);

        bool IsActive() const;
        void Update() const;
    };

}// namespace veb
