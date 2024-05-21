#pragma once

#include <cstdint>

namespace veb {

class Entity final {
public:
    const uint16_t id;

    Entity();
    ~Entity();

    Entity(const Entity &entity);

    operator uint16_t() const {
        return id;
    }
};

} // namespace veb
