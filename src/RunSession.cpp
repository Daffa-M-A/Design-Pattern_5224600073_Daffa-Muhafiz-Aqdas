#include "RunSession.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>

RunSession::RunSession() {
    std::srand(std::time(0));
}

void RunSession::generateCan() {
    can.clear();
    // Isi can dengan 30 batu acak
    for (int i = 0; i < 30; ++i) {
        RockType rt = static_cast<RockType>(std::rand() % 3);
        int smooth = (std::rand() % 10) + 1; // 1-10
        can.push_back({rt, smooth});
    }
    // Shuffle the can
    std::random_shuffle(can.begin(), can.end());
}

void RunSession::drawToHand() {
    // Isi hand sampai 5 batu
    while (hand.size() < 5 && !can.empty()) {
        hand.push_back(can.back());
        can.pop_back();
    }
}

void RunSession::startRound() {
    playsLeft = 3;
    discardsLeft = 3;
    hand.clear();
    generateCan();
    drawToHand();
}

void RunSession::displayHand() const {
    std::cout << "--- Your Hand ---\n";
    for (size_t i = 0; i < hand.size(); ++i) {
        std::cout << "[" << i + 1 << "] " 
                  << hand[i].getTypeName() 
                  << " (Smoothness: " << hand[i].smoothness << ")\n";
    }
}

std::vector<Stone> RunSession::playStones(const std::vector<int>& indices) {
    std::vector<Stone> played;
    if (indices.empty() || indices.size() > 3 || playsLeft <= 0) return played;

    // Ambil batu dari belakang agar index tidak bergeser saat dihapus
    std::vector<int> sortedIndices = indices;
    std::sort(sortedIndices.rbegin(), sortedIndices.rend());

    for (int idx : sortedIndices) {
        if (idx >= 0 && idx < hand.size()) {
            played.push_back(hand[idx]);
            hand.erase(hand.begin() + idx);
        }
    }
    playsLeft--;
    drawToHand();
    return played;
}

bool RunSession::discardStones(const std::vector<int>& indices) {
    if (indices.empty() || indices.size() > 5 || discardsLeft <= 0) return false;

    std::vector<int> sortedIndices = indices;
    std::sort(sortedIndices.rbegin(), sortedIndices.rend());

    for (int idx : sortedIndices) {
        if (idx >= 0 && idx < hand.size()) {
            hand.erase(hand.begin() + idx);
        }
    }
    discardsLeft--;
    drawToHand();
    return true;
}