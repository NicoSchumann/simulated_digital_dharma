#pragma once

#include <string>
#include <vector>

class Agent {
public:
    Agent(int id);
    void decide();
    void receiveFeedback(int reward);
    int getID() const;
    int getScore() const;
    bool getDecision() const;

private:
    int _id;
    int _score;
    bool _currentDecision;
    std::vector<int> _memory;  // einfache History
};