#pragma once

#include <optional>
#include "Game.h"

class GUI {
public:
    GUI(Game& game);
    ~GUI();
    void run();

private:
    Game& game;
    SDL_Window* window;
    SDL_Renderer* renderer;

    void drawBoard();
}; 