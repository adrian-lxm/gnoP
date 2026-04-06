//
// Created by adrian on 06.04.26.
//
#pragma once
#include <SDL2/SDL.h>
#include "Player.h"

class Game {
    bool running = false;
    SDL_Window* window;
    SDL_Renderer* renderer;
    Player player1;
    Player player2;

public:
    bool create();
    void run();
    void render();
    void handleEvent(SDL_Event* event);
    void free();
    void setRenderer(SDL_Renderer* renderer) {
        this->renderer = renderer;
    }

};
