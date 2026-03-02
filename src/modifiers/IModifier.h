#pragma once
#include <string>
#include "../Stone.h"

class IModifier {
public:
    virtual ~IModifier() = default;
    virtual std::string getName() const = 0;
    virtual std::string getDescription() const = 0;
    
    virtual void modifyStone(Stone& stone) const {}
    
    virtual int modifyBounces(const Stone& stone, int currentBounces) const { 
        return currentBounces; 
    }
};