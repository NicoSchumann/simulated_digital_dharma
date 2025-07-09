// -- Environment.hpp --
#pragma once

#include "KaelonEvent.hpp"
#include "DecisionStrategy.hpp"
#include "KaelonAsyncBase.hpp"
#include <memory>
#include <mutex>
#include <random>
#include <thread>
#include <vector>

struct Agent {
    int id;
    int score = 0;
    std::shared_ptr<DecisionStrategy> strategy;
    std::unordered_map<int, std::vector<bool>> partnerHistory;

    Agent(int id_, std::shared_ptr<DecisionStrategy> strat) : id(id_), strategy(std::move(strat)) {}

    bool decide(int partnerId) {
        return strategy->decide(partnerId, partnerHistory);
    }

    std::string getStrategyName() const {
        return strategy->getStrategy();
    }
};

class Environment {
public:
    void registerObserver(KaelonBase* obs) {
        std::scoped_lock lock(mutex_);
        observers.push_back(obs);
    }

    void runSimulation(int rounds = 10) {
        std::thread([this, rounds]() {
            initializeAgents();
            for (int i = 0; i < rounds; ++i) {
                step();
                publishSnapshot();
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }).detach();
    }

private:
    std::vector<std::unique_ptr<Agent>> agents;
    std::vector<KaelonBase*> observers;
    std::mutex mutex_;

    void initializeAgents() {
        agents.clear();
        for (int i = 0; i < 8; ++i) {
            auto strategy = randomStrategy();
            agents.emplace_back(std::make_unique<Agent>(i, strategy));
        }
    }

    void step() {
        for (size_t i = 0; i < agents.size(); ++i) {
            for (size_t j = i + 1; j < agents.size(); ++j) {
                bool a = agents[i]->decide(agents[j]->id);
                bool b = agents[j]->decide(agents[i]->id);
                if (a) agents[i]->score += b ? 3 : 0;
                if (b) agents[j]->score += a ? 3 : 0;
                agents[i]->partnerHistory[agents[j]->id].push_back(b);
                agents[j]->partnerHistory[agents[i]->id].push_back(a);
            }
        }
    }

    void publishSnapshot() {
        KaelonEvent evt;
        evt.type = KaelonEvent::SnapshotUpdate;
        for (const auto& ag : agents) {
            evt.snapshot.push_back({ag->id, ag->score, ag->getStrategyName()});
        }
        std::scoped_lock lock(mutex_);
        for (auto* obs : observers) {
            obs->enqueueEvent(evt);
        }
    }

    std::shared_ptr<DecisionStrategy> randomStrategy(); // implemented elsewhere
};

