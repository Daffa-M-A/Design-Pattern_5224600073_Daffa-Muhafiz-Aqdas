#include "ScoringSystem.h"

int ScoringSystem::calculatePlayScore(const std::vector<Stone>& playedStones) {
    if (playedStones.empty()) return 0;

    int totalSmoothness = 0;
    int totalBounces = 0;
    int numStones = playedStones.size();

    for (const auto& stone : playedStones) {
        totalSmoothness += stone.smoothness;

        // Hitung power awal
        float power = stone.getBaseValue() / static_cast<float>(stone.smoothness);
        float friction = stone.getFriction();
        int bounces = 1; // Minimal pantul 1 kali

        // Logika pantulan: selama power < 1, tambah friction dan pantulan
        while (power < 1.0f) {
            power += friction;
            bounces++;
        }
        
        totalBounces += bounces;
    }

    // Rumus: jumlah smoothness x (jumlah batu x total skipping/bounces)
    return totalSmoothness * (numStones * totalBounces);
}