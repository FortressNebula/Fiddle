#pragma once

// Very simple renderable state
// Stores a vertex array object and a shader
// Also stores a vertex count stored in vertices length
typedef struct {
    unsigned int vertices_length;
    unsigned int VAO;
    unsigned int shader_program;
} StaticRenderable;

// Simple renderable constructor
// Vertex-format: X Y Z
// Elements: NO
// @param renderable a pointer to the static renderable
// @param sizeof_vertices sizeof(vertices)
// @param vertices your list of vertices, with each vertex being 3 numbers for XYZ 
// @param shader your OpenGL shader program handle
void elementless_dataless_static_renderable(StaticRenderable *renderable, int sizeof_vertices, float vertices[], unsigned int shader);