#pragma once
#include "IModifier.h"
#include <cstdlib> 

class BurningLeaf : public IModifier {
public:
    std::string getName() const override { return "Burning Leaf"; }
    std::string getDescription() const override { return "Igneous friction becomes 0.15"; }
    
    void modifyStone(Stone& stone) const override {
        if (stone.type == RockType::IGNEOUS) {
            stone.friction = 0.15f; 
        }
    }
};

class SolidifiedLeaf : public IModifier {
public:
    std::string getName() const override { return "Solidified Leaf"; }
    std::string getDescription() const override { return "Sedimentary base value becomes 5"; }
    
    void modifyStone(Stone& stone) const override {
        if (stone.type == RockType::SEDIMENTARY) {
            stone.baseValue = 5.0f; 
        }
    }
};

class FloatingLeaf : public IModifier {
public:
    std::string getName() const override { return "Floating Leaf"; }
    std::string getDescription() const override { return "10% chance for Metamorphic rock to bounce 1 extra time"; }
    
    int modifyBounces(const Stone& stone, int currentBounces) const override {
        if (stone.type == RockType::METAMORPHIC) {
            if (std::rand() % 100 < 10) {
                return currentBounces + 1; 
            }
        }
        return currentBounces;
    }
};