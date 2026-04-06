//
// Created by adrian on 06.04.26.
//

#pragma once
#include <SDL_rect.h>

struct Player {
    int points;
    const float yVelocity = 80;
    SDL_FRect rect {
        0, 0, 10, 50
    };
};
