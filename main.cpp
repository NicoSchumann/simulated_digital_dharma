// Projekt: Simuliertes Digitales Dharma
// Proposal: Observing emergently ethic at agent-based systems

#include "environment.hpp"
#include "kaelon.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <thread>
#include <chrono>

bool running = true;

void  evaluateStrategies(std::vector<std::string>& inputs, std::vector<Strategy>&agents) {

    for (std::string& str: inputs){
        switch(str[0]) {
            case 'n':
            case 'N':
            {
                agents.push_back(Strategy::NICE);
                break;
            }
            case 'r':
            case 'R':
            {
                agents.push_back(Strategy::RUDE);
                break;
            }
            case 't':
            case 'T':
            {
                agents.push_back(Strategy::TITFORTAT);
                break;
            }
            case 'x':
            case 'X':
            {
                agents.push_back(Strategy::RANDOM);
                break;
            }
            case 'l':
            case 'L':
            {
                agents.push_back(Strategy::LAST10);
                break;
            }
            default:
            {
                agents.push_back(Strategy::RUDE);
            }
        }
    }
}

int main() {

    // We could redirect the input stream from a file
    std::vector<std::string> input;
    for (std::string tmp; std::cin >> tmp; input.push_back(tmp)) {};
    std::vector<Strategy> agents;
    evaluateStrategies(input, agents);

    Environment env(agents);

    // It's a lambda fuction (closure)
    std::thread kaelonThread([&env](){
        while (running) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            auto stats = env.snapshot();
            Kaelon::analyze(stats);
        }
    });

    env.showStats();
    std::cout << "\n====================\n";

    for (size_t i = 0; i < 10; ++ i) {
        if (i > 0) {
            env.survivalOfFittest();
        }
        for (size_t j = 0; j < 50; ++j) {
            env.runCycle();
        }
    }
    env.showStats();

    running = false;
    kaelonThread.join();
    
    return 0;
}
