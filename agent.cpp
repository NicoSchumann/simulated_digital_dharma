#include "agent.hpp"
#include <cstdlib>

Agent::Agent(int id, std::shared_ptr<DecisionStrategy> strategy)
: _id{id}, _score{0}, _strategy(std::move(strategy))
{}

void Agent::decide(int partnerID) {
    _currentDecision = _strategy->decide(partnerID, _partnerHistory);
}

void Agent::receiveFeedback(int reward) {
    _score += reward;
}

void Agent::memorize(const Agent& other) {
    _partnerHistory[other.getID()].push_back(other.getCurrentDecision());
}

int Agent::getID() const { return _id; }

std::string_view Agent::getStrategyName() const { return _strategy->getName(); }
std::shared_ptr<DecisionStrategy> Agent::getStrategy() const { return _strategy; }

int Agent::getScore() const { return _score; }

void Agent::resetScore() { _score = 0; }

bool Agent::getCurrentDecision() const { return _currentDecision; }

std::ostream& operator<<(std::ostream& os, const Agent& agent) {
    return os << agent.getID() 
    << " " << agent.getScore()
    << " " << agent.getStrategyName();
}
