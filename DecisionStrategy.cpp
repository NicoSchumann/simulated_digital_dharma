#include "DecisionStrategy.hpp"
#include <cstdlib>

bool TitForTatStrategy::decide(int partnerID,
    const std::unordered_map<int, std::vector<bool>>& memory) const {
    auto it = memory.find(partnerID);
    if (it == memory.end() || it->second.empty())
        return true; // Default: cooperate
    return it->second.back(); // React to last action
}
std::string_view TitForTatStrategy::getName() const { return "tit-for-tat"; }

bool NiceStrategy::decide(int, const std::unordered_map<int, std::vector<bool>>&) const { return true;
}
std::string_view NiceStrategy::getName() const {return "nice";}

bool RudeStrategy::decide(int, const std::unordered_map<int, std::vector<bool>>&) const{
    return false;
}
std::string_view RudeStrategy::getName() const { return "rude";}


bool RandomStrategy::decide(int, const std::unordered_map<int, std::vector<bool>>&) const {
    return std::rand() % 2 == 1;
}
std::string_view RandomStrategy::getName() const {return "random"; }

bool Last10Strategy::decide(int partnerID, const std::unordered_map<int, std::vector<bool>>& memory) const {
    auto mem_it = memory.find(partnerID);
    // no entry
    if (mem_it == memory.end()) {
        return true;
    }
    int ctr = 0;
    // Returns true if the the partner agent cooperated the last 10 sequents in time
    for (std::vector<bool>::const_reverse_iterator it = mem_it->second.crbegin(); it != mem_it->second.crend() && ctr++ < 10; ++it) {
        if (*it == false) {
            return false;
        }
    }
    return true;
}
std::string_view Last10Strategy::getName() const { return "last_10_true"; }


std::ostream& operator<<(std::ostream& os, const DecisionStrategy& strategy) {
    return os << strategy.getName();
}
