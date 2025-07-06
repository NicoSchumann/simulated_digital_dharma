#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>

class DecisionStrategy {
public:
    virtual bool decide(int partnerID,
        const std::unordered_map<int, std::vector<bool>>& memory) const = 0;
    virtual std::string_view getName() const = 0;
    virtual ~DecisionStrategy() = default;
};

class TitForTatStrategy : public DecisionStrategy {
public:
    bool decide(int partnerID,
        const std::unordered_map<int, std::vector<bool>>& memory) const override;
    std::string_view getName() const override;
};

class NiceStrategy : public DecisionStrategy {
public:
    bool decide(int partnerID, const std::unordered_map<int, std::vector<bool>>& memory) const override;
    std::string_view getName() const override;
};

class RandomStrategy : public DecisionStrategy {
public:
    bool decide(int ParterID, const std::unordered_map<int, std::vector<bool>>& memory) const override;
    std::string_view getName() const override;
};

class RudeStrategy : public DecisionStrategy {
public:
    bool decide(int partnerID, const std::unordered_map<int, std::vector<bool>>& memory) const override;
    std::string_view getName() const override;
};

class Last10Strategy : public DecisionStrategy {
public:
    bool decide(int partnerID, const std::unordered_map<int, std::vector<bool>>& memory) const override;
    std::string_view getName() const override;
};

std::ostream& operator<<(std::ostream& os, const DecisionStrategy& strategy);
