#pragma once
#include <iostream>

class Board {
private:
    char spaces[9];

public:
    Board();
    void reset();
    void display() const;
    bool makeMove(int position, char marker);
    bool isValidMove(int position) const;
    char getSpace(int position) const;
    std::string getBoardState() const;
    bool checkWinCondition(char marker) const;
    bool isFull() const;
};