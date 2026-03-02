#pragma once
#include <memory>
#include <vector>
#include "modifiers/IModifier.h"

class ShopSystem {
public:
    std::unique_ptr<IModifier> openShop();
};