# Tic-Tac-Toe AI

This project is a Tic-Tac-Toe game that uses an AI algorithm to play against a human player. The game is implemented in C++ and uses SDL2 for the visual display.

## Features

- Play Tic-Tac-Toe against an AI
- Uses a Minimax algorithm for AI moves
- Visual display using SDL2
- Simple command-line interface

## Requirements

- C++17
- SDL2

## Setup

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/tic-tac-toe-ai.git
   ```

2. Build the project:
   ```bash
   cd tic-tac-toe-ai
   make
   ```

3. Run the game:
   ```bash
   ./tictactoe
   ```

## AI Algorithm

The AI uses the Minimax algorithm to determine the best move. This algorithm evaluates all possible moves and selects the one that maximizes the AI's chances of winning while minimizing the player's chances.

## Visual Display

The game uses SDL2 to render the Tic-Tac-Toe board and handle user input. The display is a simple 3x3 grid where players can click to make their moves.

## License

This project is licensed under the MIT License.