#pragma once
#include "Player.h"

class HumanPlayer : public Player {
public:
    HumanPlayer(char marker, const std::string& name);
    int getMove(const Board& board) override;
};      