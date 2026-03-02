#include "ScoringSystem.h"

int ScoringSystem::calculatePlayScore(const std::vector<Stone>& playedStones, const std::vector<std::unique_ptr<IModifier>>& activeLeaves) {
    if (playedStones.empty()) return 0;

    int totalSmoothness = 0;
    int totalBounces = 0;
    int numStones = playedStones.size();

    for (const auto& originalStone : playedStones) {
        Stone currentStone = originalStone;

        for (const auto& leaf : activeLeaves) {
            leaf->modifyStone(currentStone); 
        }

        totalSmoothness += currentStone.smoothness;

        float power = currentStone.baseValue / static_cast<float>(currentStone.smoothness);
        float friction = currentStone.friction;
        int bounces = 1; 
        while (power < 1.0f) {
            power += friction;
            bounces++;
        }

        for (const auto& leaf : activeLeaves) {
            bounces = leaf->modifyBounces(currentStone, bounces);
        }
        
        totalBounces += bounces;
    }

    return totalSmoothness * (numStones * totalBounces);
}