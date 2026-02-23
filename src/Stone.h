#pragma once
#include <string>

enum class RockType {
    IGNEOUS,
    SEDIMENTARY,
    METAMORPHIC
};

struct Stone {
    RockType type;
    int smoothness; // 1 - 10

    float getBaseValue() const {
        switch(type) {
            case RockType::IGNEOUS: return 3.0f;
            case RockType::SEDIMENTARY: return 7.0f;
            case RockType::METAMORPHIC: return 1.0f;
        }
        return 1.0f;
    }

    float getFriction() const {
        switch(type) {
            case RockType::IGNEOUS: return 0.2f;
            case RockType::SEDIMENTARY: return 0.1f;
            case RockType::METAMORPHIC: return 0.3f;
        }
        return 0.1f;
    }

    std::string getTypeName() const {
        switch(type) {
            case RockType::IGNEOUS: return "Igneous";
            case RockType::SEDIMENTARY: return "Sedimentary";
            case RockType::METAMORPHIC: return "Metamorphic";
        }
        return "Unknown";
    }
};