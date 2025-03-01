#pragma once

#include <SDL3/SDL.h>
#include <stdbool.h>

bool process_input(SDL_Event event);

typedef struct
{
    int mouse_x;
    int mouse_y;

    int mode;
} Camera;

extern Camera camera;