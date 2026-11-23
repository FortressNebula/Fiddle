#include "shaders.h"
#include <stdio.h>

static char* read_file(char* file_name)
{
    FILE *fp;
    fp = fopen(file_name, "r");

    if (fp == NULL)
    {
        // Failed to open file!
        printf("Failed to open file, %s", file_name);
        return NULL;
    }

    char* buffer = NULL;
    size_t len;
    ssize_t bytes_read = getdelim(&buffer, &len, '\0', fp);

    fclose(fp);

    if (bytes_read == -1)
    {
        // Failed to read file!
        printf("Failed to read file, %s", file_name);
        return NULL;
    }

    return buffer;    
}

unsigned int create_shader(GLenum type, char* file_name)
{
    const char* source = read_file(file_name);
    if (source == NULL)
    {
        printf("Failed to create shader, invalid source!");
        return -1;
    }

    unsigned int shader;
    shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        printf("Failed to compile shader!");
        return -1;
    }

    return shader;
}

unsigned int create_shader_program(char* frag_file, char* vert_file)
{
    unsigned int frag, vert, program;

    frag = create_shader(GL_FRAGMENT_SHADER, frag_file);
    if (frag == -1)
    {
        printf("Failed to create fragment shader %s", frag_file);
        return -1;
    }

    vert = create_shader(GL_VERTEX_SHADER, vert_file);
    if (vert == -1)
    {
        glDeleteShader(frag);
        printf("Failed to create vertex shader %s", vert_file);
        return -1;
    }

    program = glCreateProgram();
    glAttachShader(program, frag);
    glAttachShader(program, vert);
    glLinkProgram(program);

    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glDeleteProgram(program);
        printf("Failed to link program!");
        return -1;
    }

    glDeleteShader(frag);
    glDeleteShader(vert);

    return program;
}