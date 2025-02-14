#include <SDL.h>
#include "Game.h"

class SDLGUI {
public:
    SDLGUI(Game& game) : game(game) {
        SDL_Init(SDL_INIT_VIDEO);
        window = SDL_CreateWindow("Tic-Tac-Toe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 300, 300, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    }

    ~SDLGUI() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void run() {
        bool running = true;
        while (running) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    running = false;
                } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        int x = event.button.x / 100;
                        int y = event.button.y / 100;
                        int position = y * 3 + x;
                        if (game.makeMove(position, 'X')) {
                            if (game.checkWinner() || game.checkTie()) {
                                game.displayResult();
                                running = false;
                            } else {
                                int aiMove = game.getAIPlayer()->getMove(game.getBoard());
                                game.makeMove(aiMove, 'O');
                                if (game.checkWinner() || game.checkTie()) {
                                    game.displayResult();
                                    running = false;
                                }
                            }
                        }
                    }
                }
            }

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderClear(renderer);
            drawBoard();
            SDL_RenderPresent(renderer);
        }
    }

private:
    Game& game;
    SDL_Window* window;
    SDL_Renderer* renderer;

    void drawBoard() {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        for (int i = 1; i < 3; ++i) {
            SDL_RenderDrawLine(renderer, i * 100, 0, i * 100, 300);
            SDL_RenderDrawLine(renderer, 0, i * 100, 300, i * 100);
        }

        for (int i = 0; i < 9; ++i) {
            char marker = game.getBoard().getSpace(i);
            if (marker != ' ') {
                SDL_Rect rect = { (i % 3) * 100 + 20, (i / 3) * 100 + 20, 60, 60 };
                if (marker == 'X') {
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                } else {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                }
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
};