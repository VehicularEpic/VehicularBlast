#pragma once

#include "veb/component/ComponentMesh.hpp"
#include "veb/component/ComponentPosition.hpp"
#include "veb/component/ComponentRotation.hpp"

#include <map>
#include <memory>
#include <typeindex>

namespace veb {

class Entity {
private:
    std::map<std::type_index, std::shared_ptr<void>> components;

public:
    Entity() = default;
    virtual ~Entity() = default;

    template<typename T>
    void Add(T component) {
        components.insert(std::make_pair<std::type_index, std::shared_ptr<T>>(typeid(T), std::make_shared<T>(component)));
    }

    template<typename T>
    std::shared_ptr<T> Get() const {
        auto component = components.find(typeid(T));

        if (components.end() == component)
            return nullptr;

        return std::static_pointer_cast<T>(component->second);
    }
};

} // namespace veb
