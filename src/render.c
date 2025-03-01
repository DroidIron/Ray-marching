#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <cglm/cglm.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "render.h"
#include "window.h"
#include "shader.h"
#include "input.h"

#define NUM_PROGRAMS 9

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

unsigned int programs[NUM_PROGRAMS];

// -------

// Variables:
// Camera:
vec3 camera_pos = (vec3){0.0f, 0.0f, -6.0f};
vec3 camera_direction = (vec3){0.0f, 0.0f, -1.0f};
vec3 camera_up = (vec3){0.0f, 1.0f, 0.0f};
vec3 camera_right;
int last_mode = 0;

void init_render(void)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    camera.mode = 0;

    for (int i = 0; i < NUM_PROGRAMS; i++)
    {
        programs[i] = 0;
    }

    // VAO, VBO & Vertex shader (Same for each program!):
    VBO = create_vbo(vertices, sizeof(vertices), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    vertex_shader_src = read_file("shader_src/vs.txt");
    vertex_shader = create_vertex_shader(vertex_shader_src);
    // ------------------------------------------

    // Shaders:
    fragment_shader_src = read_file("shader_src/fs.txt");
    fragment_shader = create_fragment_shader(fragment_shader_src);
    
    char *fragment_shader_src2 = read_file("shader_src/fs2.txt");
    unsigned int fragment_shader2 = create_fragment_shader(fragment_shader_src2);

    char *fragment_shader_src3 = read_file("shader_src/fs3.txt");
    unsigned int fragment_shader3 = create_fragment_shader(fragment_shader_src3);

    char *fragment_shader_src4 = read_file("shader_src/fs4.txt");
    unsigned int fragment_shader4 = create_fragment_shader(fragment_shader_src4);

    char *fragment_shader_src5 = read_file("shader_src/fs5.txt");
    unsigned int fragment_shader5 = create_fragment_shader(fragment_shader_src5);
    
    char *fragment_shader_src6 = read_file("shader_src/fs6.txt");
    unsigned int fragment_shader6 = create_fragment_shader(fragment_shader_src6);
    
    char *fragment_shader_src7 = read_file("shader_src/fs7.txt");
    unsigned int fragment_shader7 = create_fragment_shader(fragment_shader_src7);

    char *fragment_shader_src8 = read_file("shader_src/fs8.txt");
    unsigned int fragment_shader8 = create_fragment_shader(fragment_shader_src8);

    char *fragment_shader_src9 = read_file("shader_src/fs9.txt");
    unsigned int fragment_shader9 = create_fragment_shader(fragment_shader_src9);

    // Programs:
    programs[0] = glCreateProgram();
    glAttachShader(programs[0], vertex_shader);
    glAttachShader(programs[0], fragment_shader);
    glLinkProgram(programs[0]);
    glDeleteShader(fragment_shader);

    programs[1] = glCreateProgram();
    glAttachShader(programs[1], vertex_shader);
    glAttachShader(programs[1], fragment_shader2);
    glLinkProgram(programs[1]);
    glDeleteShader(fragment_shader2);

    programs[2] = glCreateProgram();
    glAttachShader(programs[2], vertex_shader);
    glAttachShader(programs[2], fragment_shader3);
    glLinkProgram(programs[2]);
    glDeleteShader(fragment_shader3);

    programs[3] = glCreateProgram();
    glAttachShader(programs[3], vertex_shader);
    glAttachShader(programs[3], fragment_shader4);
    glLinkProgram(programs[3]);
    glDeleteShader(fragment_shader4);

    programs[4] = glCreateProgram();
    glAttachShader(programs[4], vertex_shader);
    glAttachShader(programs[4], fragment_shader5);
    glLinkProgram(programs[4]);
    glDeleteShader(fragment_shader5);

    programs[5] = glCreateProgram();
    glAttachShader(programs[5], vertex_shader);
    glAttachShader(programs[5], fragment_shader6);
    glLinkProgram(programs[5]);
    glDeleteShader(fragment_shader6);

    programs[6] = glCreateProgram();
    glAttachShader(programs[6], vertex_shader);
    glAttachShader(programs[6], fragment_shader7);
    glLinkProgram(programs[6]);
    glDeleteShader(fragment_shader7);

    programs[7] = glCreateProgram();
    glAttachShader(programs[7], vertex_shader);
    glAttachShader(programs[7], fragment_shader8);
    glLinkProgram(programs[7]);
    glDeleteShader(fragment_shader8);

    programs[8] = glCreateProgram();
    glAttachShader(programs[8], vertex_shader);
    glAttachShader(programs[8], fragment_shader9);
    glLinkProgram(programs[8]);
    glDeleteShader(fragment_shader9);

    glDeleteShader(vertex_shader);
}

void render(double time)
{
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (last_mode != camera.mode)
    {
        switch (camera.mode)
        {
            case 0:
                glUseProgram(programs[0]);
                break;
            case 1:
                glUseProgram(programs[1]);
                break;
            case 2:
                glUseProgram(programs[2]);
                break;
            case 3:
                glUseProgram(programs[3]);
                break;
            case 4:
                glUseProgram(programs[4]);
                break;
            case 5:
                glUseProgram(programs[5]);
                break;
            case 6:
                glUseProgram(programs[6]);
                break;
            case 7:
                glUseProgram(programs[7]);
                break;
            case 8:
                glUseProgram(programs[8]);
            default:
                break;
        }    
    }
    else if (last_mode == 0 && camera.mode == 0)
    {
        glUseProgram(programs[0]);
    }

    last_mode = camera.mode;

    unsigned int screen_size_loc = glGetUniformLocation(programs[camera.mode], "screen_size");
    unsigned int camera_pos_loc = glGetUniformLocation(programs[camera.mode], "camera_position");
    unsigned int camera_direction_loc = glGetUniformLocation(programs[camera.mode], "camera_direction");
    unsigned int camera_up_loc = glGetUniformLocation(programs[camera.mode], "camera_up");
    unsigned int camera_right_loc = glGetUniformLocation(programs[camera.mode], "camera_right");
    unsigned int time_loc = glGetUniformLocation(programs[camera.mode], "time");
    unsigned int mouse_loc = glGetUniformLocation(programs[camera.mode], "mouse");

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

    vec2 mouse;
    mouse[0] = camera.mouse_x * -1;
    mouse[1] = camera.mouse_y * -1;

    glUniform2fv(screen_size_loc, 1, (float*)screen_size);
    glUniform3fv(camera_pos_loc, 1, (float*)camera_pos);
    glUniform3fv(camera_direction_loc, 1, (float*)camera_direction);
    glUniform3fv(camera_up_loc, 1, (float*)camera_up);
    glUniform3fv(camera_right_loc, 1, (float*)camera_right);
    glUniform1f(time_loc, time);
    glUniform2fv(mouse_loc, 1, (float*)mouse);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    SDL_GL_SwapWindow(window->sdl_window);
}

void destroy_programs(void)
{
    for (int i = 0; i < NUM_PROGRAMS; i++)
    {
        glDeleteProgram(programs[i]);
    }
}