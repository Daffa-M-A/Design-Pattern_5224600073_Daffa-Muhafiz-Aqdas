#pragma once
#include <vector>
#include <memory>
#include "Stone.h"
#include "modifiers/IModifier.h"

class ScoringSystem {
public:
    int calculatePlayScore(const std::vector<Stone>& playedStones, const std::vector<std::unique_ptr<IModifier>>& activeLeaves);
};