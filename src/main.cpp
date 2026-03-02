#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <memory>
#include "RunSession.h"
#include "ScoringSystem.h"
#include "ShopSystem.h"
#include "modifiers/IModifier.h"

using namespace std;

// Fungsi bantu untuk mengubah input teks ("1 2 3") menjadi vector index
vector<int> parseInput(const string& input) {
    vector<int> indices;
    stringstream ss(input);
    int num;
    while (ss >> num) {
        indices.push_back(num - 1);
    }
    return indices;
}

int main() {
    vector<int> targetScores = {300, 450, 600};
    ScoringSystem scorer;
    ShopSystem shop;
    
    // Inventory/Koleksi Leaf milik pemain yang akan terus dibawa antar ronde
    vector<unique_ptr<IModifier>> activeLeaves;

    cout << "===================================\n";
    cout << "      STONE SKIPPING: THE GAME     \n";
    cout << "===================================\n";

    for (int round = 1; round <= 3; ++round) {
        int target = targetScores[round - 1];
        RunSession session;
        session.startRound();
        
        int currentScore = 0;

        cout << "\n>>> ROUND " << round << " STARTS! <<<\n";
        
        // Tampilkan Leaf apa saja yang sedang aktif
        if (!activeLeaves.empty()) {
            cout << "[Active Leaves]: ";
            for (const auto& leaf : activeLeaves) {
                cout << leaf->getName() << " | ";
            }
            cout << "\n";
        }

        // Loop per ronde
        while (session.getPlaysLeft() > 0 && currentScore < target) {
            cout << "\n-----------------------------------\n";
            cout << "Score: " << currentScore << " / " << target << "\n";
            cout << "Plays left: " << session.getPlaysLeft() 
                 << " | Discards left: " << session.getDiscardsLeft() << "\n";
            
            session.displayHand();

            cout << "\nActions: \n1. Play (e.g., '1 1 3' or '1 2' - max 3 stones)\n2. Discard (e.g., '2 1 2 3 4 5' - max 5 stones)\n";
            cout << "Choose action (1 or 2): ";
            int action;
            cin >> action;
            cin.ignore();

            if (action == 1) {
                cout << "Enter stone numbers to PLAY (separated by space): ";
                string input;
                getline(cin, input);
                vector<int> indices = parseInput(input);
                
                if (indices.size() > 0 && indices.size() <= 3) {
                    vector<Stone> played = session.playStones(indices);
                    
                    // Hitung skor dengan menyertakan activeLeaves
                    int scoreGained = scorer.calculatePlayScore(played, activeLeaves);
                    currentScore += scoreGained;
                    cout << "\n> You skipped stones and scored " << scoreGained << " points!\n";
                } else {
                    cout << "Invalid play. Must select 1 to 3 stones.\n";
                }

            } else if (action == 2) {
                if (session.getDiscardsLeft() > 0) {
                    cout << "Enter stone numbers to DISCARD (separated by space): ";
                    string input;
                    getline(cin, input);
                    vector<int> indices = parseInput(input);
                    
                    if (session.discardStones(indices)) {
                        cout << "\n> Stones discarded.\n";
                    } else {
                        cout << "Invalid discard.\n";
                    }
                } else {
                    cout << "No discards left!\n";
                }
            }
        }

        // Cek kondisi menang/kalah per ronde
        if (currentScore >= target) {
            cout << "\n*** ROUND " << round << " CLEARED! ***\n";
            
            // Masuk Shop jika bukan ronde terakhir
            if (round < 3) {
                auto newLeaf = shop.openShop();
                if (newLeaf) {
                    
                    // --- LOGIKA BARU: Batasan 1 Leaf ---
                    if (!activeLeaves.empty()) {
                        cout << "\n> You replaced [" << activeLeaves[0]->getName() 
                             << "] with [" << newLeaf->getName() << "]!\n";
                        activeLeaves.clear(); // Hapus Leaf yang lama
                    } else {
                        cout << "\n> You acquired: [" << newLeaf->getName() << "]!\n";
                    }
                    
                    activeLeaves.push_back(move(newLeaf)); // Masukkan Leaf yang baru
                    // -----------------------------------
                    
                } else {
                    cout << "\n> You skipped the shop.\n";
                }
            }
        } else {
            cout << "\n*** GAME OVER! Target not reached. ***\n";
            return 0; // Menghentikan program jika kalah
        }
    }

    cout << "\n===================================\n";
    cout << "YOU BEAT ALL ROUNDS! CONGRATULATIONS!\n";
    cout << "===================================\n";

    return 0;
}