#include "ScoringSystem.h"

int ScoringSystem::calculatePlayScore(const std::vector<Stone>& playedStones, const std::vector<std::unique_ptr<IModifier>>& activeLeaves) {
    if (playedStones.empty()) return 0;

    int totalSmoothness = 0;
    int totalBounces = 0;
    int numStones = playedStones.size();

    for (const auto& originalStone : playedStones) {
        // Buat salinan batu agar kita bisa mengubah stat-nya tanpa merusak batu asli di tangan
        Stone currentStone = originalStone;

        // --- STRUCTURAL PATTERN: DECORATOR CHAIN ---
        // 1. Terapkan Modifier yang mengubah stat dasar batu (Burning & Solidified)
        for (const auto& leaf : activeLeaves) {
            leaf->modifyStone(currentStone); 
        }

        totalSmoothness += currentStone.smoothness;

        // Hitung power awal menggunakan stat yang mungkin sudah dimodifikasi oleh Leaf
        float power = currentStone.baseValue / static_cast<float>(currentStone.smoothness);
        float friction = currentStone.friction;
        int bounces = 1; // Minimal pantul 1 kali

        // Logika pantulan: selama power < 1, tambah friction dan pantulan
        while (power < 1.0f) {
            power += friction;
            bounces++;
        }

        // --- STRUCTURAL PATTERN: DECORATOR CHAIN ---
        // 2. Terapkan Modifier yang memanipulasi hasil akhir pantulan (Floating Leaf)
        for (const auto& leaf : activeLeaves) {
            bounces = leaf->modifyBounces(currentStone, bounces);
        }
        
        totalBounces += bounces;
    }

    // Rumus akhir: jumlah smoothness x (jumlah batu x total skipping/bounces)
    return totalSmoothness * (numStones * totalBounces);
}