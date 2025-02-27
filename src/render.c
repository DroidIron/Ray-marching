#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <cglm/cglm.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "render.h"
#include "window.h"
#include "shader.h"

float vertices[] = {
    // First triangle
    -1.0f, -1.0f, 0.0f,  // Bottom-left
     1.0f, -1.0f, 0.0f,  // Bottom-right
     1.0f,  1.0f, 0.0f,  // Top-right

    // Second triangle
     1.0f,  1.0f, 0.0f,  // Top-right
    -1.0f,  1.0f, 0.0f,  // Top-left
    -1.0f, -1.0f, 0.0f   // Bottom-left
};

// Shader:
unsigned int VAO = 0;
unsigned int VBO = 0;

char *vertex_shader_src = NULL;
unsigned vertex_shader = 0;

char *fragment_shader_src = NULL;
unsigned fragment_shader = 0;

unsigned int program = 0;
// -------

// Variables:
// Camera:
vec3 camera_pos = (vec3){0.0f, 0.0f, -5.0f};
vec3 camera_direction = (vec3){0.0f, 0.0f, -1.0f};
vec3 camera_up = (vec3){0.0f, 1.0f, 0.0f};
vec3 camera_right;

void init_render(void)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    VBO = create_vbo(vertices, sizeof(vertices), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    vertex_shader_src = read_file("vs.txt");
    vertex_shader = create_vertex_shader(vertex_shader_src);

    fragment_shader_src = read_file("fs.txt");
    fragment_shader = create_fragment_shader(fragment_shader_src);

    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

void render(void)
{
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(program);

    unsigned int screen_size_loc = glGetUniformLocation(program, "screen_size");
    unsigned int camera_pos_loc = glGetUniformLocation(program, "camera_position");
    unsigned int camera_direction_loc = glGetUniformLocation(program, "camera_direction");
    unsigned int camera_up_loc = glGetUniformLocation(program, "camera_up");
    unsigned int camera_right_loc = glGetUniformLocation(program, "camera_right");

    // Screen size:
    vec2 screen_size;
    screen_size[0] = window->width;
    screen_size[1] = window->height;
    
    // Camera:
    glm_vec3_sub(camera_direction, camera_pos, camera_direction);
    glm_vec3_normalize(camera_direction);

    glm_vec3_cross(camera_up, camera_direction, camera_right);
    glm_vec3_normalize(camera_right);

    glm_vec3_cross(camera_direction, camera_right, camera_up);
    glm_vec3_normalize(camera_up);

    glUniform2fv(screen_size_loc, 1, (float*)screen_size);
    glUniform3fv(camera_pos_loc, 1, (float*)camera_pos);
    glUniform3fv(camera_direction_loc, 1, (float*)camera_direction);
    glUniform3fv(camera_up_loc, 1, (float*)camera_up);
    glUniform3fv(camera_right_loc, 1, (float*)camera_right);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    SDL_GL_SwapWindow(window->sdl_window);
}