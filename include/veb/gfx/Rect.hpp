#pragma once

#include <cstdint>

namespace veb {

class Rect {
private:
    uint32_t object = 0;

    Rect();
    ~Rect();

    Rect(const Rect &r) = delete;
    Rect(Rect &&r) noexcept = delete;

public:
    void Render() const;

    static const Rect &GetInstance();
};

} // namespace veb
