#pragma once
#include <vector>
#include "Stone.h"

class RunSession {
private:
    std::vector<Stone> can; // Deck
    std::vector<Stone> hand;
    int playsLeft;
    int discardsLeft;

    void generateCan();
    void drawToHand();

public:
    RunSession();
    
    void startRound();
    void displayHand() const;
    
    int getPlaysLeft() const { return playsLeft; }
    int getDiscardsLeft() const { return discardsLeft; }
    int getHandSize() const { return hand.size(); }
    const std::vector<Stone>& getHand() const { return hand; }

    std::vector<Stone> playStones(const std::vector<int>& indices);
    bool discardStones(const std::vector<int>& indices);
};