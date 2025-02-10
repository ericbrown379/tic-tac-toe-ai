#pragma once
#include "Board.h"
#include <string>

class Player {
protected:
    char marker;
    std::string name;

public:
    Player(char marker, const std::string& name) : marker(marker), name(name) {}
    virtual ~Player() = default;
    virtual int getMove(const Board& board) = 0;
    char getMarker() const { return marker; }
    std::string getName() const { return name; }
};