#pragma once
#include <vector>
#include "Stone.h"

class ScoringSystem {
public:
    // Mengembalikan skor dari satu kali 'play'
    int calculatePlayScore(const std::vector<Stone>& playedStones);
};