#include "AIPlayer.h"
#include <iostream>
#include <limits>

AIPlayer::AIPlayer(char marker, const std::string& key) 
    : Player(marker, "AI"), learningRate(0.1), apiKey(key) {}

int AIPlayer::getMove(const Board& board) {
    int bestMove = -1;
    int bestValue = std::numeric_limits<int>::min();

    for (int i = 0; i < 9; ++i) {
        if (board.isValidMove(i)) {
            Board newBoard = board;
            newBoard.makeMove(i, marker);
            int moveValue = minimax(newBoard, 0, false);
            if (moveValue > bestValue) {
                bestMove = i;
                bestValue = moveValue;
            }
        }
    }
    return bestMove;
}

int AIPlayer::minimax(Board board, int depth, bool isMaximizing) {
    if (board.checkWinCondition(marker)) return 10 - depth;
    if (board.checkWinCondition(opponentMarker())) return depth - 10;
    if (board.isFull()) return 0;

    if (isMaximizing) {
        int bestValue = std::numeric_limits<int>::min();
        for (int i = 0; i < 9; ++i) {
            if (board.isValidMove(i)) {
                board.makeMove(i, marker);
                int value = minimax(board, depth + 1, false);
                board.makeMove(i, ' '); // Undo move
                bestValue = std::max(bestValue, value);
            }
        }
        return bestValue;
    } else {
        int bestValue = std::numeric_limits<int>::max();
        for (int i = 0; i < 9; ++i) {
            if (board.isValidMove(i)) {
                board.makeMove(i, opponentMarker());
                int value = minimax(board, depth + 1, true);
                board.makeMove(i, ' '); // Undo move
                bestValue = std::min(bestValue, value);
            }
        }
        return bestValue;
    }
}

char AIPlayer::opponentMarker() const {
    return marker == 'X' ? 'O' : 'X';
}

void AIPlayer::updateMoveValue(const std::string& state, int move, bool won) {
    // Implement logic to update move value
}

void AIPlayer::saveToFile() const {
    // Implement logic to save to file
}

void AIPlayer::loadFromFile() {
    // Implement logic to load from file
} 