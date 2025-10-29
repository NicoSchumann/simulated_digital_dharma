#pragma once

#include "agent.hpp"
#include <vector>

enum class Strategy { NICE, TITFORTAT, RUDE, RANDOM, LAST10 };

class Environment {
public:
    Environment(std::vector<Strategy>&);
    void runCycle();
    void showStats();
    void survivalOfFittest();

private:
    int maxID;
    std::vector<Agent> _agents;
    void simulateInteraction(Agent& a, Agent& b);
};