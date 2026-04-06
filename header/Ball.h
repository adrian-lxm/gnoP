//
// Created by adrian on 06.04.26.
//

#pragma once
#include <SDL2/SDL.h>


struct Ball {
    SDL_FRect rect {
        0, 0, 25, 25
    };
    float velocity[2] = {0, 0};

};