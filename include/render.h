#pragma once

#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <cglm/cglm.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void init_render(void);
void render(double time);
void destroy_programs(void);