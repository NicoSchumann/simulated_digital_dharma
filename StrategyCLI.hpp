// -- StrategyCLI.hpp --
#pragma once

#include "StrategyManager.hpp"
#include "DecisionStrategy.hpp"
#include "strategies/NiceStrategy.hpp"
#include "strategies/RudeStrategy.hpp"
#include "strategies/RandomStrategy.hpp"
#include "strategies/TitForTatStrategy.hpp"
#include <string>
#include <iostream>
#include <sstream>

class StrategyCLI {
public:
    static void registerBuiltins() {
        StrategyManager::instance().registerStrategy("nice", std::make_shared<NiceStrategy>());
        StrategyManager::instance().registerStrategy("rude", std::make_shared<RudeStrategy>());
        StrategyManager::instance().registerStrategy("random", std::make_shared<RandomStrategy>());
        StrategyManager::instance().registerStrategy("tit-for-tat", std::make_shared<TitForTatStrategy>());
    }

    static void repl() {
        std::string line;
        std::cout << "[StrategyCLI] Type 'list', 'clear', or 'exit'.\n";
        while (true) {
            std::cout << "> ";
            std::getline(std::cin, line);
            std::istringstream iss(line);
            std::string cmd;
            iss >> cmd;

            if (cmd == "exit") break;
            else if (cmd == "list") list();
            else if (cmd == "clear") StrategyManager::instance().clear();
            else std::cout << "Unknown command\n";
        }
    }

private:
    static void list() {
        std::cout << "[StrategyCLI] Registered strategies:\n";
        for (std::string_view name : {"nice", "rude", "random", "tit-for-tat"}) {
            if (StrategyManager::instance().get(name))
                std::cout << " - " << name << '\n';
        }
    }
};

