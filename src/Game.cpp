//
// Created by adrian on 06.04.26.
//
#include "Game.h"
#include <chrono>
#include <unordered_map>

#define LOGICAL_WIDTH 512
#define LOGICAL_HEIGHT 256

std::unordered_map<SDL_Keycode, bool> pressedKeys;
bool Game::create() {

    window = SDL_CreateWindow("gnoP", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LOGICAL_WIDTH, LOGICAL_HEIGHT, SDL_WINDOW_RESIZABLE);
    if (!window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        SDL_Quit();
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer creation failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    SDL_RenderSetLogicalSize(renderer, LOGICAL_WIDTH, LOGICAL_HEIGHT);
    player1.rect.x = 20;
    player1.rect.y = (LOGICAL_HEIGHT - 40) / 2;
    player2.rect.x = LOGICAL_WIDTH - 30;
    player2.rect.y = (LOGICAL_HEIGHT - 40) / 2;

    running = true;
    return true;
}

void Game::run() {
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) handleEvent(&event);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        render();
        SDL_RenderPresent(renderer);
    }
}

void update(float delta) {

}

auto start = std::chrono::high_resolution_clock::now();
void Game::render() {
    auto end = std::chrono::high_resolution_clock::now();
    float deltatime = std::chrono::duration<float>(end - start).count();
    start = end;

    update(deltatime);

    SDL_RenderFillRectF(renderer, &player1.rect);
    SDL_RenderFillRectF(renderer, &player2.rect);

}

void Game::handleEvent(SDL_Event *event) {
    switch (event->type) {
        case SDL_QUIT:
            running = false;
            break;

        case SDL_KEYDOWN:
            pressedKeys[event->key.keysym.sym] = true;
            break;

        case SDL_KEYUP:
            pressedKeys[event->key.keysym.sym] = false;
            break;

        default:
            break;
    }
}

void Game::free() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
