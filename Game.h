#pragma once
#include "Board.h"
#include "Player.h"
#include "AIPlayer.h"

class Game {
private:
    Board board;
    Player* player1;
    Player* player2;
    bool isGameOver;

public:
    Game(Player* p1, Player* p2);
    ~Game();
    void start();
    void playTurn();
    bool checkWinner();
    bool checkTie();
    void displayResult();
    void reset();
    void display() const;
    bool makeMove(int position, char marker);
    bool isValidMove(int position) const;
    char getSpace(int position) const;
    std::string getBoardState() const;
    bool checkWinCondition(char marker) const;
    bool isFull() const;
};