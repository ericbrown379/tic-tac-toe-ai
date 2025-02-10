#include "HumanPlayer.h"
#include <iostream>

HumanPlayer::HumanPlayer(char marker, const std::string& name) : Player(marker, name) {}

int HumanPlayer::getMove(const Board& board) {
    int move;
    std::cout << "Enter your move (1-9): ";
    std::cin >> move;
    return move - 1; // Convert to 0-based index
} 