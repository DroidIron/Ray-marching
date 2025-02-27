#include "glad/glad.h"
#include <stdio.h>
#include <stdlib.h>

unsigned int create_vbo(const float *data, size_t size, GLenum usage)
{
    // Creates a VBO (Vertex buffer object) and unbinds it.
    // To bind the VBO use: glBindBuffer(GL_ARRAY_BUFFER, NAME);

    if (usage != GL_STATIC_DRAW && usage != GL_STATIC_READ && usage != GL_STATIC_COPY &&
    usage != GL_DYNAMIC_DRAW && usage != GL_DYNAMIC_READ && usage != GL_DYNAMIC_COPY)
    {
        printf("Error: Invalid VBO mode\n");
        return 0;
    }

    unsigned int VBO = 0;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    return VBO;
}

unsigned int create_ebo(unsigned int *indices, size_t size, GLenum usage)
{
    if (usage != GL_STATIC_DRAW && usage != GL_STATIC_READ && usage != GL_STATIC_COPY &&
        usage != GL_DYNAMIC_DRAW && usage != GL_DYNAMIC_READ && usage != GL_DYNAMIC_COPY)
    {
        printf("Invalid EBO mode\n");
        return 0;
    }

    // EBO creation:
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, usage);

    return EBO;
}

unsigned int create_vertex_shader(const char *src)
{
    // Shader creation:
    unsigned int v_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(v_shader, 1, &src, NULL);
    glCompileShader(v_shader);

    // Error checking:
    int success;
    char info_log[512];
    glGetShaderiv(v_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(v_shader, 512, NULL, info_log);
        printf("Failed to create vertex shader: %s\n", info_log);
        return 0;
    }

    return v_shader;
}

unsigned int create_fragment_shader(const char *src)
{
    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &src, NULL);
    glCompileShader(fragment_shader);

    // Error checking:
    int success;
    char info_log[512];
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
        printf("Failed to create fragment shader: %s\n", info_log);
        return 0;
    }

    return fragment_shader;
}

char* read_file(const char *file_path)
{
    FILE *fptr = fopen(file_path, "rb"); // Open in binary mode for accurate size
    if (!fptr) {
        printf("Failed to open file: %s\n", file_path);
        return NULL;
    }

    // Determine file size
    fseek(fptr, 0, SEEK_END);
    long file_size = ftell(fptr);
    rewind(fptr);

    if (file_size == -1) {
        fclose(fptr);
        printf("Failed to determine file size.\n");
        return NULL;
    }

    // Allocate buffer (+1 for null terminator)
    char *buffer = (char*)malloc(file_size + 1);
    if (!buffer) {
        fclose(fptr);
        printf("Memory allocation failed.\n");
        return NULL;
    }

    // Read file content
    size_t bytes_read = fread(buffer, 1, file_size, fptr);
    if (bytes_read != (size_t)file_size) {
        free(buffer);
        fclose(fptr);
        printf("Failed to read entire file.\n");
        return NULL;
    }

    // Null-terminate the buffer
    buffer[bytes_read] = '\0';

    fclose(fptr);
    return buffer;
}