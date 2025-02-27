#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "window.h"

Window *window = NULL;

int create_window(char *title, int window_width, int window_height)
{
    window = malloc(sizeof(Window));
    if (!window)
    {
        printf("Could not locate memory for the window object\n");
        return 1;
    }

    // OpenGL:
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    window->sdl_window = SDL_CreateWindow(
        title,
        window_width,
        window_height,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL
    );
    if (!window->sdl_window)
    {
        printf("Could not create the SDL window: %s\n", SDL_GetError());
        free(window);
        return 1;
    }

    window->gl_context = SDL_GL_CreateContext(window->sdl_window);
    if (!window->gl_context)
    {
        printf("Could not create the SDL gl_context\n", SDL_GetError());
        SDL_DestroyWindow(window->sdl_window);
        free(window);
        return 1;
    }

    SDL_GL_MakeCurrent(window->sdl_window, window->gl_context);

    window->title = title;
    window->width = window_width;
    window->height = window_height;

    return 0;
}

void cleanup_window(Window *win)
{
    if (win)
    {
        if (win->gl_context)
        {
            SDL_GL_DestroyContext(win->gl_context);
        }
        if (win->sdl_window)
        {
            SDL_DestroyWindow(win->sdl_window);
        }

        free (win);
    }
    else
    {
        return;
    }
}

void resize_window(int n_w, int n_h)
{
    window->width = n_w;
    window->height = n_h;

    glViewport(0, 0, window->width, window->height);
}