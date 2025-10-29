// -- KaelonAsyncBase.hpp --
#pragma once

#include <thread>
#include <atomic>
#include <memory>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <vector>
#include "AgentStats.hpp"

// Event structure passed to KaelonBase
struct KaelonEvent {
    enum Type {
        SnapshotUpdate,    // Environment sends current agent states
        CommandIssued      // Kaelon sends control commands
    } type;

    std::vector<AgentStats> snapshot;  // Used for SnapshotUpdate events
    // Additional fields could include: timestamp, sender ID, payload, etc.
};

// Thread-capable event consumer (base class for all Kaelon variants)
class KaelonBase {
public:
    KaelonBase();
    virtual ~KaelonBase();

    void start();                          // Start the internal thread
    void stop();                           // Stop the internal thread
    void pushEvent(const KaelonEvent&);    // Inject external event into queue

protected:
    virtual void onEvent(const KaelonEvent&) = 0;  // Must be overridden by subclass

private:
    std::atomic<bool> running;
    std::thread worker;

    std::mutex queueMutex;
    std::condition_variable cv;
    std::queue<KaelonEvent> eventQueue;

    void runLoop();                        // Internal event-processing loop
};

