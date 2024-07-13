#pragma once

#include <string>
#include <unordered_map>

namespace veb {

template<typename T>
class Registry {

private:
    std::unordered_map<std::string, T> entries;

    Registry() = default;

    Registry(const Registry &) = delete;
    Registry(Registry &&) = delete;

    Registry &operator=(const Registry &) = delete;
    Registry &operator=(Registry &&) = delete;

public:
    static Registry &Fetch() {
        static Registry registry;
        return registry;
    }

    T &Get(std::string key) {
        auto itr = entries.find(key);
        return itr->second;
    }

    const T &Get(std::string key) const {
        return Get(key);
    }

    bool Has(std::string key) {
        return entries.count(key) > 0;
    }

    void Put(std::string key, T entry) {
        entries.emplace(key, std::move(entry));
    }

    void Remove(std::string key) {
        entries.erase(key);
    }
};

} // namespace veb
