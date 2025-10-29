#include "agent.hpp"
#include "environment.hpp"
#include "DecisionStrategy.hpp"
#include <random>
#include <iostream>
#include <algorithm>

Environment::Environment(std::vector<Strategy>& agentsStrategies) {

    std::shared_ptr<DecisionStrategy> niceStrategy = std::make_shared<NiceStrategy>();
    std::shared_ptr<DecisionStrategy> rudeStrategy = std::make_shared<RudeStrategy>();
    std::shared_ptr<DecisionStrategy> titfortatStrategy = std::make_shared<TitForTatStrategy>();
    std::shared_ptr<DecisionStrategy> randomStrategy = std::make_shared<RandomStrategy>();
    std::shared_ptr<DecisionStrategy> last10Strategy = std::make_shared<Last10Strategy>();

    maxID = 0;
    for (size_t i = 0; i < agentsStrategies.size(); ++i) {

        // switch over the 1st char of numAgents[i]
        switch (agentsStrategies[i]) {
            case Strategy::NICE:
            {
                _agents.push_back(Agent(maxID, niceStrategy));
                break;
            }
            case Strategy::TITFORTAT:
            {
                _agents.push_back(Agent(maxID, titfortatStrategy));
                break;
            }
            case Strategy::RUDE:
            {
                _agents.push_back(Agent(maxID, rudeStrategy));
                break;
            }
            case Strategy::RANDOM:
            {
                _agents.push_back(Agent(maxID, randomStrategy));
                break;
            }
            case Strategy::LAST10:
            {
                _agents.push_back(Agent(maxID, last10Strategy));
                break;
            }
            default:
            {
                _agents.push_back(Agent(maxID, rudeStrategy));
            }
        }
        ++ maxID;
    }
}

void Environment::runCycle() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, _agents.size() - 1);

    for (size_t i = 0; i < _agents.size(); ++i) {
        size_t j = dis(gen);
        if (i == j) continue;

        simulateInteraction( _agents[i], _agents[j] );
    }
}


void  Environment::simulateInteraction(Agent& agent_A, Agent& agent_B ) {
        agent_A.decide(agent_B.getID());
        agent_B.decide(agent_A.getID());

        bool a = agent_A.getCurrentDecision();
        bool b = agent_B.getCurrentDecision();

        // simple reward system
        if (a && b) {
            agent_A.receiveFeedback(3);
            agent_B.receiveFeedback(3);
        } else if (a && !b) {
            agent_A.receiveFeedback(0);
            agent_B.receiveFeedback(5);
        } else if (!a && b) {
            agent_A.receiveFeedback(5);
            agent_B.receiveFeedback(0);
        } else {   // (!a && !b)
            agent_A.receiveFeedback(1);
            agent_B.receiveFeedback(1);
        }

        // memorize partner agent's decision
        agent_A.memorize(agent_B);
        agent_B.memorize(agent_A);
}

void Environment::survivalOfFittest() {
    std::sort(_agents.begin(), _agents.end(), [](const Agent& a, const Agent& b) { return a.getScore() >= b.getScore();});
    for (auto& a : _agents) {
        a.resetScore();
    }
    _agents.back() = std::move(Agent(++maxID, _agents.front().getStrategy()));
}

void Environment::showStats() {
    std::sort(_agents.begin(), _agents.end(), [](const Agent& a, const Agent& b){ return a.getScore() >= b.getScore();});
    for (const auto& a: _agents) {
        std::cout << "Agent " << a.getID()
                  << " | Score: " << a.getScore()
                  << " | Strategy: " << a.getStrategyName()
                  << '\n';
    }
}