#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Create a GLFWwindow window. Returns NULL if unsuccessful
GLFWwindow* make_window(int width, int height, char* name);