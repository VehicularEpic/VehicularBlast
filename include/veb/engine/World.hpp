#pragma once

#include "veb/engine/Entity.hpp"

#include <functional>
#include <vector>

namespace veb {

class World {
private:
    std::vector<Entity> entities{};

public:
    World() = default;
    ~World() = default;

    void Process(std::function<void(const Entity &)> process) const {
        for (const Entity &entity : entities)
            process(entity);
    }

    void AddEntity(Entity entity) {
        entities.push_back(entity);
    }

    void Clear() {
        entities.clear();
    }
};

} // namespace veb
