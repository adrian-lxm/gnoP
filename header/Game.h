//
// Created by adrian on 06.04.26.
//
#pragma once
#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include "Player.h"
#include "Ball.h"

class Game {
    bool running = false;
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Texture* pointCount;
    int texW;
    int texH;
    Player player1;
    Player player2;
    Ball ball;

    void update(float deltatime);
    void updatePointCount();
    void resetBall();

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
