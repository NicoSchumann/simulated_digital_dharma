#pragma once

#include "agent.hpp"
#include <vector>

class Environment {
public:
    Environment(size_t numAgents);
    void runCycle();
    void showStats() const;

private:
    std::vector<Agent> _agents;
    void simulateInteraction(Agent& a, Agent& b);
};