#pragma once

#include "glad/glad.h"

unsigned int create_vbo(const float *data, size_t size, GLenum usage);
unsigned int create_ebo(unsigned int *indices, size_t size, GLenum usage);
unsigned int create_vertex_shader(const char *src);
unsigned int create_fragment_shader(const char *src);
char* read_file(const char *file_path);