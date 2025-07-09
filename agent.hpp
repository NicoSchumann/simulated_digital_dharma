#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include "DecisionStrategy.hpp"

class Agent {
public:
    Agent(int id, std::shared_ptr<DecisionStrategy> strategy);
    void decide(int partnerID);
    void receiveFeedback(int reward);
    void memorize(const Agent& other);
    int getID() const;
    int getScore() const;
    void resetScore();
    bool getCurrentDecision() const;
    std::string_view getStrategyName() const;
    std::shared_ptr<DecisionStrategy> getStrategy() const;

private:
    int _id;
    int _score;
    bool _currentDecision;
    std::shared_ptr<DecisionStrategy> _strategy;
    // simple history
    std::unordered_map<int, std::vector<bool>> _partnerHistory;
};

std::ostream& operator<<(std::ostream& os, const Agent& agent);