// -- main.cpp --
#include "Environment.hpp"
#include "KaelonObserver.hpp"
#include <thread>
#include <chrono>

int main() {
    Environment env;
    KaelonObserver kaelon;

    kaelon.start();
    env.registerObserver(&kaelon);

    env.runSimulation(20);  // Run 20 rounds (configurable)

    // Allow time for final snapshot processing
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    kaelon.stop();
    return 0;
}

