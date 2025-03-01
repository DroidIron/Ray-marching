#include <SDL3/SDL.h>
#include <stdbool.h>
#include <stdio.h>

#include "input.h"
#include "window.h"

Camera camera;

float mx = 0;
float my = 0;

bool process_input(SDL_Event event)
{
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
        {
            return false;
        }
        if (event.type == SDL_EVENT_WINDOW_RESIZED)
        {
            resize_window(event.window.data1, event.window.data2);
        }
        if (event.type == SDL_EVENT_KEY_DOWN)
        {
            if (event.key.scancode == SDL_SCANCODE_ESCAPE)
            {
                return false;
            }

            if (event.key.scancode == SDL_SCANCODE_1)
            {
                camera.mode = 0;
            }
            if (event.key.scancode == SDL_SCANCODE_2)
            {
                camera.mode = 1;
            }
            if (event.key.scancode == SDL_SCANCODE_3)
            {
                camera.mode = 2;
            }
            if (event.key.scancode == SDL_SCANCODE_4)
            {
                camera.mode = 3;
            }
            if (event.key.scancode == SDL_SCANCODE_5)
            {
                camera.mode = 4;
            }
            if (event.key.scancode == SDL_SCANCODE_6)
            {
                camera.mode = 5;
            }
            if (event.key.scancode == SDL_SCANCODE_7)
            {
                camera.mode = 6;
            }
            if (event.key.scancode == SDL_SCANCODE_8)
            {
                camera.mode = 7;
            }
            if (event.key.scancode == SDL_SCANCODE_9)
            {
                camera.mode = 8;
            }
        }
        
        // Mouse:
        SDL_GetMouseState(&mx, &my);
        camera.mouse_x = (int)mx;
        camera.mouse_y = (int)my;

        //printf("%i %i\n", camera.mouse_x, camera.mouse_y);
    }

    return true;
}