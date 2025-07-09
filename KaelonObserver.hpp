// -- KaelonObserver.hpp --
#pragma once

#include "KaelonAsyncBase.hpp"
#include <iostream>
#include <iomanip>

// Passive logging observer that prints all incoming snapshots
class KaelonObserver : public KaelonBase {
protected:
    void onEvent(const KaelonEvent& event) override {
        if (event.type != KaelonEvent::SnapshotUpdate) return;

        std::cout << "[KaelonObserver] Snapshot received: \n";
        for (const auto& agent : event.snapshot) {
            std::cout << "  Agent " << std::setw(2) << agent.id
                      << " | Score: " << std::setw(3) << agent.score
                      << " | Strategy: " << agent.strategy << "\n";
        }
    }
};

