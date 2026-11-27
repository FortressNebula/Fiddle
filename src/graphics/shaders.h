#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Create a shader of the given time
unsigned int create_shader(GLenum type, char* file_name);
// Create a complete shader program
// Return -1 if failed
unsigned int create_shader_program(char* frag_file, char* vert_file);