#pragma once

#include "agent.hpp"

class Kaelon {
public:
    void observe(const Agent& a, const Agent& b, bool cooperated);
    void adjustParameters();
};