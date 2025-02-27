#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <cglm/cglm.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "window.h"
#include "shader.h"
#include "stb_image.h"
#include "texture.h"
#include "render.h"

#define WINDOW_TITLE "3D engine"
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 800

// Game loop:
bool game_running = true;
SDL_Event event;

int init(void);

int main(int argc, char *argv[])
{
    if (init() != 0) {return 1;}
    init_render();

    while (game_running)
    { 
        glViewport(0, 0, window->width, window->height);

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                game_running = false;
            }
            if (event.type == SDL_EVENT_WINDOW_RESIZED)
            {
                resize_window(event.window.data1, event.window.data2);
            }
            if (event.type == SDL_EVENT_KEY_DOWN)
            {
                game_running = false;
            }
        }

        render();

        SDL_Delay(16);
    }

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