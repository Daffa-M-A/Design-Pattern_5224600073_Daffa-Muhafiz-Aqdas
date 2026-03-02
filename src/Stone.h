#pragma once
#include <string>

enum class RockType { IGNEOUS, SEDIMENTARY, METAMORPHIC };

struct Stone {
    RockType type;
    int smoothness; 
    float baseValue; // Sekarang jadi variabel agar bisa diubah Modifier
    float friction;  // Sekarang jadi variabel agar bisa diubah Modifier

    // Constructor untuk menetapkan nilai awal sesuai tipe
    Stone(RockType t, int s) : type(t), smoothness(s) {
        if (t == RockType::IGNEOUS) { baseValue = 3.0f; friction = 0.2f; }
        else if (t == RockType::SEDIMENTARY) { baseValue = 7.0f; friction = 0.1f; }
        else if (t == RockType::METAMORPHIC) { baseValue = 1.0f; friction = 0.3f; }
    }

    std::string getTypeName() const {
        if (type == RockType::IGNEOUS) return "Igneous";
        if (type == RockType::SEDIMENTARY) return "Sedimentary";
        return "Metamorphic";
    }
};