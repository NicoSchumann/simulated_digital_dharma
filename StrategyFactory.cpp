// -- StrategyFactory.cpp --
#include "StrategyFactory.hpp"
#include "NiceStrategy.hpp"
#include "RudeStrategy.hpp"
#include "TitForTatStrategy.hpp"
#include "RandomStrategy.hpp"

std::shared_ptr<DecisionStrategy> StrategyFactory::create(const std::string_view& name) {
    static const std::unordered_map<std::string_view, std::shared_ptr<DecisionStrategy>(*)()> registry = {
        {"nice", [] { return std::make_shared<NiceStrategy>(); }},
        {"rude", [] { return std::make_shared<RudeStrategy>(); }},
        {"tit-for-tat", [] { return std::make_shared<TitForTatStrategy>(); }},
        {"random", [] { return std::make_shared<RandomStrategy>(); }}
    };

    auto it = registry.find(name);
    if (it != registry.end()) {
        return it->second();
    }
    return std::make_shared<RandomStrategy>(); // fallback
}

std::shared_ptr<DecisionStrategy> StrategyFactory::randomStrategy() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    const auto& strategies = availableStrategies();
    std::uniform_int_distribution<> dist(0, strategies.size() - 1);
    return create(strategies[dist(gen)]);
}

std::vector<std::string_view> StrategyFactory::availableStrategies() {
    return {"nice", "rude", "tit-for-tat", "random"};
}

