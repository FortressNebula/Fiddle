#pragma once
#include "components.h"

// Very simple renderable state
// Stores a vertex array object and a shader
// Also stores a vertex count stored in vertices length
typedef struct {
    unsigned int vertices_length;
    unsigned int VAO;
    unsigned int shader_program;
} StaticRenderable;

// Makes a renderer ready to draw a StaticRenderable state
// Use a renderable constructor method to attach a renderable state
// Z-value is 0 by default, change after if needed
Renderer make_static_renderer(void);

// Attaches a simple renderable to a static renderer
// Vertex-format: X Y Z
// Elements: NO
// Uniforms: NO
// @param renderer a pointer to your static renderer
// @param sizeof_vertices sizeof(vertices)
// @param vertices your list of vertices, with each vertex being 3 numbers for XYZ 
// @param shader your OpenGL shader program handle
void elementless_dataless_static_renderable(Renderer *renderer, int sizeof_vertices, float vertices[], unsigned int shader);