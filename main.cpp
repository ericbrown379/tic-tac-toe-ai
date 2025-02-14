#include <iostream>
#include <ctime>
#include <map>
#include <vector>
#include <string>
#include "Game.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "SDLGUI.h" // Ensure this is included

using namespace std;

void drawboard(char *spaces);
void playerMove(char *spaces, char player);
bool checkWinner(char *spaces, char player, char computer);
bool checkTie(char *spaces);

int main() {
    Player* human = new HumanPlayer('X', "Player");
    Player* ai = new AIPlayer('O', "");

    Game game(human, ai);

    SDLGUI gui(game);
    gui.run();

    delete human;
    delete ai;

    return 0;
}

void drawboard(char *spaces) {
    cout << "     |     |     \n";
    cout << "  " << spaces[0] << "  |  " << spaces[1] << "  |  " << spaces[2] << "  \n";
    cout << "_____|_____|_____\n";
    cout << "     |     |     \n";
    cout << "  " << spaces[3] << "  |  " << spaces[4] << "  |  " << spaces[5] << "  \n";
    cout << "_____|_____|_____\n";
    cout << "     |     |     \n";
    cout << "  " << spaces[6] << "  |  " << spaces[7] << "  |  " << spaces[8] << "  \n";
    cout << "     |     |     \n";
}

bool checkWinner(char *spaces, char player, char computer) {
    // Implement winner check logic
    return false;
}

bool checkTie(char *spaces) {
    for (int i = 0; i < 9; i++) {
        if (spaces[i] == ' ') {
            return false;
        }
    }
    cout << "IT'S A TIE!" << endl;
    return true;
}