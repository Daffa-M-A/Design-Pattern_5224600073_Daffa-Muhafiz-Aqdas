#pragma once
#include "IModifier.h"
#include <cstdlib> // Untuk std::rand()

// 1. Burning Leaf (Buff Igneous rock)
class BurningLeaf : public IModifier {
public:
    std::string getName() const override { return "Burning Leaf"; }
    std::string getDescription() const override { return "Igneous friction becomes 0.15"; }
    
    void modifyStone(Stone& stone) const override {
        if (stone.type == RockType::IGNEOUS) {
            stone.friction = 0.15f; // Mengubah stat batu
        }
    }
};

// 2. Solidified Leaf (Buff Sedimentary rock)
class SolidifiedLeaf : public IModifier {
public:
    std::string getName() const override { return "Solidified Leaf"; }
    std::string getDescription() const override { return "Sedimentary base value becomes 5"; }
    
    void modifyStone(Stone& stone) const override {
        if (stone.type == RockType::SEDIMENTARY) {
            stone.baseValue = 5.0f; // Mengubah stat batu
        }
    }
};

// 3. Floating Leaf (Buff Metamorphic rock)
class FloatingLeaf : public IModifier {
public:
    std::string getName() const override { return "Floating Leaf"; }
    std::string getDescription() const override { return "10% chance for Metamorphic rock to bounce 1 extra time"; }
    
    int modifyBounces(const Stone& stone, int currentBounces) const override {
        if (stone.type == RockType::METAMORPHIC) {
            // Peluang 1 banding 10 (10%)
            if (std::rand() % 100 < 10) {
                return currentBounces + 1; // Pantul sekali lagi!
            }
        }
        return currentBounces;
    }
};