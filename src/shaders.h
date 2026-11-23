#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

unsigned int create_shader(GLenum type, char* file_name);
unsigned int create_shader_program(char* frag_file, char* vert_file);