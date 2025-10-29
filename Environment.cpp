// -- Environment.cpp --
#include "Environment.hpp"
#include <algorithm>

Environment::Environment() = default;

Environment::~Environment() {
    stop();
    if (worker.joinable()) worker.join();
}

void Environment::addAgent(std::shared_ptr<Agent> agent) {
    std::lock_guard<std::mutex> lock(mutex);
    agents.push_back(std::move(agent));
}

void Environment::subscribe(std::shared_ptr<KaelonBase> observer) {
    std::lock_guard<std::mutex> lock(mutex);
    observers.push_back(std::move(observer));
}

void Environment::runAsync(int rounds) {
    if (running) return;
    running = true;
    worker = std::thread([this, rounds] { loop(rounds); });
}

void Environment::stop() {
    running = false;
}

void Environment::loop(int rounds) {
    for (int r = 0; r < rounds && running; ++r) {
        {
            std::lock_guard<std::mutex> lock(mutex);
            for (size_t i = 0; i < agents.size(); ++i) {
                for (size_t j = i + 1; j < agents.size(); ++j) {
                    agents[i]->interactWith(*agents[j]);
                    agents[j]->interactWith(*agents[i]);
                }
            }
        }
        notify();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    running = false;
}

void Environment::notify() {
    std::lock_guard<std::mutex> lock(mutex);
    std::vector<AgentSnapshot> snapshot;
    for (const auto& agent : agents) {
        snapshot.push_back({ agent->getID(), agent->getScore(), agent->getStrategyName() });
    }
    KaelonEvent evt{ KaelonEvent::SnapshotUpdate, snapshot };
    for (const auto& obs : observers) {
        obs->push(evt);
    }
}

