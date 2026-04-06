//
// Created by adrian on 06.04.26.
//
#include "Game.h"
#include <chrono>
#include <unordered_map>

#define LOGICAL_WIDTH 512
#define LOGICAL_HEIGHT 256

std::unordered_map<SDL_Keycode, bool> pressedKeys;

void Game::resetBall() {
    ball.rect.x = (LOGICAL_WIDTH - ball.rect.w) / 2;
    ball.rect.y = (LOGICAL_HEIGHT - ball.rect.h) / 2;
    bool direction = rand() % 2;
    if (direction) {
        ball.velocity[0] = ball.defaultVelocity;
        ball.velocity[1] = -ball.defaultVelocity;
    } else {
        ball.velocity[0] = -ball.defaultVelocity;
        ball.velocity[1] = ball.defaultVelocity;
    }
}

bool Game::create() {

    window = SDL_CreateWindow("gnoP", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LOGICAL_WIDTH, LOGICAL_HEIGHT, SDL_WINDOW_RESIZABLE);
    if (!window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer creation failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    font = TTF_OpenFont("minecraft.ttf", 12);
    if (!font) {
        printf("Font opening creation failed: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    auto surface = TTF_RenderText_Solid(font, "0 : 0", SDL_Color(255, 255, 255, 255));
    pointCount = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(pointCount, nullptr, nullptr, &texW, &texH);

    SDL_RenderSetLogicalSize(renderer, LOGICAL_WIDTH, LOGICAL_HEIGHT);
    player1.rect.x = 20;
    player1.rect.y = (LOGICAL_HEIGHT - player1.rect.h) / 2;
    player2.rect.x = LOGICAL_WIDTH - 30;
    player2.rect.y = (LOGICAL_HEIGHT - player2.rect.h) / 2;

    resetBall();

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

bool repell = false;

void Game::update(float delta) {
    if (pressedKeys[SDLK_w] && player1.rect.y > 0) {
        player1.rect.y -= player1.yVelocity * delta;
    }

    if (pressedKeys[SDLK_s] && player1.rect.y < LOGICAL_HEIGHT - player1.rect.h) {
        player1.rect.y += player1.yVelocity * delta;
    }

    if (pressedKeys[SDLK_UP] && player2.rect.y > 0) {
        player2.rect.y -= player2.yVelocity * delta;
    }

    if (pressedKeys[SDLK_DOWN] && player2.rect.y < LOGICAL_HEIGHT - player2.rect.h) {
        player2.rect.y += player2.yVelocity * delta;
    }

    ball.rect.x += ball.velocity[0] * delta;
    ball.rect.y += ball.velocity[1] * delta;
    if (ball.rect.y <= 0 || ball.rect.y >= (LOGICAL_HEIGHT - ball.rect.h) && !repell) {
        ball.velocity[1] *= -1;
        repell = true;
    } else repell = false;

    if (SDL_HasIntersectionF(&ball.rect, &player1.rect) && !repell) {
        ball.velocity[0] *= -1;
        repell = true;
    } else repell = false;

    if (SDL_HasIntersectionF(&ball.rect, &player2.rect) && !repell) {
        ball.velocity[0] *= -1;
        repell = true;
    } else repell = false;

    if (ball.rect.x <= 0) {
        player2.points += 1;
        resetBall();
        updatePointCount();
    } else if (ball.rect.x >= LOGICAL_WIDTH) {
        player1.points += 1;
        resetBall();
        updatePointCount();
    }

}

void Game::updatePointCount() {
    auto pointText = std::format("{} : {}", player1.points, player2.points);
    auto surface = TTF_RenderText_Solid(font, pointText.c_str(), SDL_Color(255, 255, 255, 255));
    pointCount = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(pointCount, nullptr, nullptr, &texW, &texH);
}

auto start = std::chrono::high_resolution_clock::now();
void Game::render() {
    auto end = std::chrono::high_resolution_clock::now();
    float deltatime = std::chrono::duration<float>(end - start).count();
    start = end;

    update(deltatime);

    SDL_RenderDrawRect(renderer, nullptr);
    SDL_RenderFillRectF(renderer, &player1.rect);
    SDL_RenderFillRectF(renderer, &player2.rect);
    SDL_RenderFillRectF(renderer, &ball.rect);
    SDL_Rect srcRec(0, 0, texW, texH);
    SDL_Rect distRec((LOGICAL_WIDTH - texW) / 2, 10, texW, texH);
    SDL_RenderCopy(renderer, pointCount, &srcRec, &distRec);

}

void Game::handleEvent(SDL_Event* event) {
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
