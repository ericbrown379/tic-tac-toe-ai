#include "Game.h"
#include <iostream>

Game::Game(Player* p1, Player* p2) 
    : player1(p1), player2(p2), isGameOver(false) {
    board.reset();
}

Game::~Game() {
    delete player1;
    delete player2;
}

void Game::start() {
    board.display();
    while (!isGameOver) {
        playTurn();
        if (checkWinner() || checkTie()) {
            displayResult();
            isGameOver = true;
        }
    }
}

void Game::playTurn() {
    static bool isPlayer1Turn = true;
    Player* currentPlayer = isPlayer1Turn ? player1 : player2;
    
    int move = currentPlayer->getMove(board);
    board.makeMove(move, currentPlayer->getMarker());
    board.display();
    
    isPlayer1Turn = !isPlayer1Turn;
}

bool Game::checkWinner() {
    if (board.checkWinCondition(player1->getMarker())) {
        std::cout << player1->getName() << " wins!" << std::endl;
        return true;
    }
    if (board.checkWinCondition(player2->getMarker())) {
        std::cout << player2->getName() << " wins!" << std::endl;
        return true;
    }
    return false;
}

bool Game::checkTie() {
    if (board.isFull()) {
        std::cout << "It's a tie!" << std::endl;
        return true;
    }
    return false;
}

void Game::displayResult() {
    // Implement logic to display the result
} 