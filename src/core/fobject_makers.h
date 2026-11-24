#pragma once
#include "fobject.h"
#include "engine.h"

// Static mesh FObject
// Vertices have no assigned colour and the given fragment shader must colour them
int static_uncoloured_mesh_fobject(FObject* fobject, int sizeof_vertices, float vertices[], char* frag_shader_path, char* vert_shader_path);
