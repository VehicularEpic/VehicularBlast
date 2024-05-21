#pragma once

#include <cstdint>
#include <unordered_map>

namespace veb {

template<typename T>
class Components final {
private:
    std::unordered_map<uint16_t, T> registry;
    Components() = default;

    Components(const Components &) = delete;
    Components(Components &&) = delete;

    Components &operator=(const Components &) = delete;
    Components &operator=(Components &&) = delete;

    static Components<T> &Instance() {
        static Components<T> registry;
        return registry;
    }

public:
    ~Components() = default;

    static T &Get(uint16_t entity) {
        auto &components = Instance();
        auto itr = components.registry.find(entity);
        return itr->second;
    }

    static bool Has(uint16_t entity) {
        auto &components = Instance();
        return !!components.registry.count(entity);
    }

    static void Put(uint16_t entity, T component) {
        auto &components = Instance();
        auto inserted = components.registry.emplace(entity, component);

        if (!inserted.second) {
            // TODO: Override values, however it's better to not do this, but properly clean up entities instead.
            components.registry.erase(entity);
            components.registry.emplace(entity, component);
        }
    }

    static void Remove(uint16_t entity) {
        auto &components = Instance();
        components.registry.erase(entity);
    }
};

} // namespace veb
