#include <SDL2/SDL.h>
#include "Game.h"

bool running = true;
Game pongGame;

int main() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("SDL Initialisation failed: %s\n", SDL_GetError());
        return -1;
    }

    if (!pongGame.create()) {
        return -1;
    }
    pongGame.run();
    pongGame.free();

    SDL_Quit();
    return 0;
}