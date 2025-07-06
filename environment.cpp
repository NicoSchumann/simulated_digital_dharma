#include "agent.hpp"
#include "environment.hpp"
#include <random>
#include <iostream>

Environment::Environment(size_t numAgents) {
    for (size_t i = 0; i < numAgents; ++i) {
        _agents.emplace_back(i);
    }
}

void Environment::runCycle() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, _agents.size() - 1);

    for (size_t i = 0; i < _agents.size(); ++i) {
        size_t j = dis(gen);
        if (i == j) continue;

        _agents[i].decide();
        _agents[j].decide();

        bool a = _agents[i].getDecision();
        bool b = _agents[i].getDecision();

        // simple reward system
        if (a && b) {
            _agents[i].receiveFeedback(3);
            _agents[j].receiveFeedback(3);
        } else if (a && !b) {
            _agents[i].receiveFeedback(0);
            _agents[j].receiveFeedback(5);
        } else if (!a && b) {
            _agents[i].receiveFeedback(5);
            _agents[j].receiveFeedback(0);
        } else {
            _agents[i].receiveFeedback(1);
            _agents[i].receiveFeedback(1);
        }
    }
}

void Environment::showStats() const {
    for (const auto& a: _agents) {
        std::cout << "Agent " << a.getID()
                  << " | Score: " << a.getScore() << '\n';
    }
}


/*
void Environment::simulateInteraction(Agent& a, Agent& b){
    // TODO
}
*/