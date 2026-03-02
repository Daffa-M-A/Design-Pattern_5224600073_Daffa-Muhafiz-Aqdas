#include "ShopSystem.h"
#include "ModifierFactory.h"
#include <iostream>

std::unique_ptr<IModifier> ShopSystem::openShop() {
    std::cout << "\n===================================\n";
    std::cout << "          LEAF SHOP (PICK 1)       \n";
    std::cout << "===================================\n";
    
    // Tampilkan barang dagangan (memanfaatkan Factory untuk melihat deskripsi)
    auto item1 = ModifierFactory::createLeaf("Burning");
    auto item2 = ModifierFactory::createLeaf("Solidified");
    auto item3 = ModifierFactory::createLeaf("Floating");

    std::cout << "1. " << item1->getName() << " - " << item1->getDescription() << "\n";
    std::cout << "2. " << item2->getName() << " - " << item2->getDescription() << "\n";
    std::cout << "3. " << item3->getName() << " - " << item3->getDescription() << "\n";
    std::cout << "4. Skip Shop\n";
    std::cout << "Choose a leaf to add to your collection (1-4): ";

    int choice;
    std::cin >> choice;
    std::cin.ignore();

    switch(choice) {
        case 1: return ModifierFactory::createLeaf("Burning");
        case 2: return ModifierFactory::createLeaf("Solidified");
        case 3: return ModifierFactory::createLeaf("Floating");
        default: return nullptr; // Skip
    }
}