#include "ModifierFactory.h"
#include "modifiers/Leaves.h"

std::unique_ptr<IModifier> ModifierFactory::createLeaf(const std::string& leafName) {
    if (leafName == "Burning") return std::make_unique<BurningLeaf>();
    if (leafName == "Solidified") return std::make_unique<SolidifiedLeaf>();
    if (leafName == "Floating") return std::make_unique<FloatingLeaf>();
    
    return nullptr;
}