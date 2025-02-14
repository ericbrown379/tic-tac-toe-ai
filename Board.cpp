#include "Board.h"
#include <iostream>

// Typically you'll have an array of winning combos:
static int WIN_COMBOS[8][3] = {
    {0,1,2}, {3,4,5}, {6,7,8}, // rows
    {0,3,6}, {1,4,7}, {2,5,8}, // columns
    {0,4,8}, {2,4,6}           // diagonals
};

Board::Board() {
    reset();
}

void Board::reset() {
    for (int i = 0; i < 9; ++i) {
        spaces[i] = ' ';
    }
}

void Board::display() const {
    std::cout << " " << spaces[0] << " | " << spaces[1] << " | " << spaces[2] << " \n";
    std::cout << "---|---|---\n";
    std::cout << " " << spaces[3] << " | " << spaces[4] << " | " << spaces[5] << " \n";
    std::cout << "---|---|---\n";
    std::cout << " " << spaces[6] << " | " << spaces[7] << " | " << spaces[8] << " \n";
}

bool Board::makeMove(int position, char marker) {
    if (isValidMove(position)) {
        spaces[position] = marker;
        return true;
    }
    return false;
}

bool Board::isValidMove(int position) const {
    return position >= 0 && position < 9 && spaces[position] == ' ';
}

char Board::getSpace(int position) const {
    return spaces[position];
}

std::string Board::getBoardState() const {
    // Example: "X O X ... "
    std::string state;
    for (int i = 0; i < 9; ++i) {
        state += (spaces[i] == ' ' ? '.' : spaces[i]);
    }
    return state;
}

bool Board::checkWinCondition(char marker) const {
    // Check each winning combo
    for (auto &combo : WIN_COMBOS) {
        if (spaces[combo[0]] == marker &&
            spaces[combo[1]] == marker &&
            spaces[combo[2]] == marker) {
            return true;
        }
    }
    return false;
}

bool Board::isFull() const {
    for (int i = 0; i < 9; i++) {
        if (spaces[i] == ' ') return false;
    }
    return true;
} 