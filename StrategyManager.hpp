// -- StrategyManager.hpp --
#pragma once

#include "DecisionStrategy.hpp"
#include <memory>
#include <unordered_map>
#include <mutex>
#include <string_view>

class StrategyManager {
public:
    static StrategyManager& instance() {
        static StrategyManager singleton;
        return singleton;
    }

    std::shared_ptr<DecisionStrategy> get(const std::string_view& name) {
        std::lock_guard<std::mutex> lock(mutex);
        auto it = registry.find(name);
        if (it != registry.end()) return it->second;
        return nullptr;
    }

    void registerStrategy(const std::string_view& name, std::shared_ptr<DecisionStrategy> strategy) {
        std::lock_guard<std::mutex> lock(mutex);
        registry[name] = std::move(strategy);
    }

    void clear() {
        std::lock_guard<std::mutex> lock(mutex);
        registry.clear();
    }

private:
    StrategyManager() = default;
    std::unordered_map<std::string_view, std::shared_ptr<DecisionStrategy>> registry;
    std::mutex mutex;
};

