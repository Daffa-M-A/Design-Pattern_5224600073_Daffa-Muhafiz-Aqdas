#pragma once
#include <memory>
#include <vector>
#include "modifiers/IModifier.h"

class ShopSystem {
public:
    // Menampilkan toko dan mengembalikan Leaf yang dibeli (bisa null jika di-skip)
    std::unique_ptr<IModifier> openShop();
};