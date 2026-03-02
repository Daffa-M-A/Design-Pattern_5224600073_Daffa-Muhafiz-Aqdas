#pragma once
#include <vector>
#include <memory>
#include "Stone.h"
#include "modifiers/IModifier.h"

class ScoringSystem {
public:
    // Sekarang fungsi ini menerima daftar Leaf yang sedang aktif
    int calculatePlayScore(const std::vector<Stone>& playedStones, const std::vector<std::unique_ptr<IModifier>>& activeLeaves);
};