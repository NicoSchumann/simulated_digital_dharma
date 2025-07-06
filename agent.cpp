#include "agent.hpp"

Agent::Agent(int id)
: _id{id}, _score{0}
{}

void Agent::decide() {
    // Dummy decision: Always cooperating (replace later)
    _currentDecision = true;
}

void Agent::receiveFeedback(int reward) {
    _score += reward;
}

int Agent::getID() const { return _id; }
int Agent::getScore() const { return _score; }
bool Agent::getDecision() const { return _currentDecision; }
