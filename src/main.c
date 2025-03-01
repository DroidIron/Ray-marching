#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <cglm/cglm.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "window.h"
#include "shader.h"
#include "input.h"
#include "stb_image.h"
#include "texture.h"
#include "render.h"

#define WINDOW_TITLE "3D engine"
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 800

// Game loop:
#define TARGET_FPS 60
#define FRAME_TIME (1000 / 60)

bool game_running = true;
SDL_Event event;

int init(void);

int main(int argc, char *argv[])
{
    if (init() != 0) {return 1;}
    init_render();

    Uint64 last_tick = SDL_GetPerformanceCounter();
    double total_time = 0.0;
    double frequency = (double)SDL_GetPerformanceFrequency();

    camera.mode = 0;

    while (game_running)
    { 
        Uint64 frame_start = SDL_GetPerformanceCounter();
        
        Uint64 current_tick = SDL_GetPerformanceCounter();
        double delta_time = (current_tick - last_tick) / frequency;
        last_tick = current_tick;

        total_time += delta_time;

        glViewport(0, 0, window->width, window->height);

        if (!process_input(event)) {return false;}

        render(total_time);

        Uint64 frame_end = SDL_GetPerformanceCounter();
        double elapsed_time = (frame_end - frame_start) * 1000 / SDL_GetPerformanceFrequency();
        if (elapsed_time < FRAME_TIME)
        {
            SDL_Delay((Uint32)(FRAME_TIME - elapsed_time));
        }
    }

    destroy_programs();
    cleanup_window(window);

    SDL_Quit();

    return 0;
}

int init(void)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        printf("Could not initialize SDL video: %s\n", SDL_GetError());
        return 1;
    }

    if (create_window(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT) != 0) {return 1;}

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        printf("Could not load GLAD\n");
        return 1;
    }

    // Depth buffer:
    glEnable(GL_DEPTH_TEST);

    return 0;
}