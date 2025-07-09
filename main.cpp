// -- main.cpp --
#include "Environment.hpp"
#include "KaelonObserver.hpp"
#include "StrategyCLI.hpp"
#include <thread>
#include <iostream>

int main() {
    StrategyCLI::registerBuiltins();

    Environment env(10);
    KaelonObserver observer;
    env.attach(&observer);

    std::thread envThread([&env]() {
        env.run(50); // run for 50 rounds
    });

    std::thread cliThread([]() {
        StrategyCLI::repl();
    });

    envThread.join();
    cliThread.join();

    return 0;
}

