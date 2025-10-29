// -- Environment.hpp --
#pragma once

#include "Agent.hpp"
#include "KaelonAsyncBase.hpp"
#include <vector>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <memory>

class Environment : public std::enable_shared_from_this<Environment> {
public:
    Environment();
    ~Environment();

    void addAgent(std::shared_ptr<Agent> agent);
    void runAsync(int rounds = 100);
    void stop();
    void subscribe(std::shared_ptr<KaelonBase> observer);

private:
    void loop(int rounds);
    void notify();

    std::vector<std::shared_ptr<Agent>> agents;
    std::vector<std::shared_ptr<KaelonBase>> observers;

    std::thread worker;
    std::mutex mutex;
    std::atomic<bool> running{false};
};
