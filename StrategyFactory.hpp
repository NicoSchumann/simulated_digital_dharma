// -- StrategyFactory.hpp --
#pragma once

#include "DecisionStrategy.hpp"
#include <memory>
#include <vector>
#include <random>
#include <string_view>
#include <unordered_map>

class StrategyFactory {
public:
    static std::shared_ptr<DecisionStrategy> create(const std::string_view& name);
    static std::shared_ptr<DecisionStrategy> randomStrategy();

private:
    static std::vector<std::string_view> availableStrategies();
};
