#pragma once
#include <string>
#include "../Stone.h"

class IModifier {
public:
    virtual ~IModifier() = default;
    virtual std::string getName() const = 0;
    virtual std::string getDescription() const = 0;
    
    // Dipanggil SEBELUM menghitung pantulan (untuk Burning & Solidified)
    virtual void modifyStone(Stone& stone) const {}
    
    // Dipanggil SETELAH menghitung pantulan (untuk Floating Leaf)
    virtual int modifyBounces(const Stone& stone, int currentBounces) const { 
        return currentBounces; 
    }
};