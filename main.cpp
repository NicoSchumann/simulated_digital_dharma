// Projekt: Simuliertes Digitales Dharma
// Zweck: Beobachtung emergenter Ethik in agentenbasierten Systemen

#include <iostream>
#include <vector>
#include <random>

class Agent {
public:
    Agent(int id) : id(id), score(0) {}

    void decide() {
        // Dummy-Entscheidung: Immer kooperieren (später ersetzen)
        currentDecision = true;
    }

    void receiveFeedback(int reward) {
        score += reward;
    }

    int getID() const { return id; }
    int getScore() const { return score; }
    bool getDecision() const { return currentDecision; }

private:
    int id;
    int score;
    bool currentDecision;
};

class Environment {
public:
    Environment(size_t numAgents) {
        for (size_t i = 0; i < numAgents; ++i) {
            agents.emplace_back(i);
        }
    }

    void runCycle() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, agents.size() - 1);

        for (size_t i = 0; i < agents.size(); ++i) {
            size_t j = dis(gen);
            if (j == i) continue;

            agents[i].decide();
            agents[j].decide();

            bool a = agents[i].getDecision();
            bool b = agents[j].getDecision();

            // einfaches Belohnungssystem
            if (a && b) {
                agents[i].receiveFeedback(3);
                agents[j].receiveFeedback(3);
            } else if (a && !b) {
                agents[i].receiveFeedback(0);
                agents[j].receiveFeedback(5);
            } else if (!a && b) {
                agents[i].receiveFeedback(5);
                agents[j].receiveFeedback(0);
            } else {
                agents[i].receiveFeedback(1);
                agents[j].receiveFeedback(1);
            }
        }
    }

    void showStats() const {
        for (const auto& a : agents) {
            std::cout << "Agent " << a.getID()
                      << " | Score: " << a.getScore() << '\n';
        }
    }

private:
    std::vector<Agent> agents;
};

int main() {
    Environment env(10);
    for (size_t i = 0; i < 50; ++i) {
        env.runCycle();
    }
    env.showStats();
    return 0;
}
