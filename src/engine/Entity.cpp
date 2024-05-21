#include "veb/engine/Entity.hpp"

#include <climits>

static uint8_t entities[USHRT_MAX];

static uint16_t GetEntityId() {
    for (uint16_t i = 0; i < USHRT_MAX; i++)
        if (!entities[i]) {
            entities[i]++;
            return i;
        }

    return 0; // TODO: What to do here if all entities are assigned?
}

namespace veb {

Entity::Entity() : id(GetEntityId()) {}

Entity::~Entity() {
    entities[id]--;
}

Entity::Entity(const Entity &entity) : id(entity.id) {
    entities[id]++;
}

} // namespace veb
