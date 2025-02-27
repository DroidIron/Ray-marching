#pragma once

#include <SDL3/SDL.h>

typedef struct
{
    char *title;
    int width;
    int height;

    SDL_Window *sdl_window;
    SDL_GLContext gl_context;
} Window;

int create_window(char *title, int window_width, int window_height);
void cleanup_window(Window *win);
void resize_window(int n_w, int n_h);

extern Window *window;