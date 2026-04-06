//
// Created by adrian on 06.04.26.
//

#pragma once
#include <SDL2/SDL.h>


struct Ball {
    const float defaultVelocity = 50;
    SDL_FRect rect {
        0, 0, 10, 10
    };
    float velocity[2] = {0, 0};
};