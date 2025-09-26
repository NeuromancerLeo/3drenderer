#include "stddef.h"
#include "array.h"
#include "mesh.h"

mesh_t mesh = {
    .vertices = NULL,
    .faces = NULL,
    .rotation = {0, 0, 0}
};

vec3_t cube_vertices[N_CUBE_VERTICES] = {
    {.x = -1, .y = -1, .z = -1}, // 1
    {.x = -1, .y =  1, .z = -1}, // 2
    {.x =  1, .y =  1, .z = -1}, // 3
    {.x =  1, .y = -1, .z = -1}, // 4
    {.x =  1, .y =  1, .z =  1}, // 5
    {.x =  1, .y = -1, .z =  1}, // 6
    {.x = -1, .y =  1, .z =  1}, // 7
    {.x = -1, .y = -1, .z =  1}, // 8
}; 


triface_t cube_faces[N_CUBE_FACES] = {
    // front
    {.index_a = 1, .index_b = 2, .index_c = 3},
    {.index_a = 1, .index_b = 3, .index_c = 4},
    // right
    {.index_a = 4, .index_b = 3, .index_c = 5},
    {.index_a = 4, .index_b = 5, .index_c = 6},
    // back
    {.index_a = 6, .index_b = 5, .index_c = 7},
    {.index_a = 6, .index_b = 7, .index_c = 8},
    // left
    {.index_a = 8, .index_b = 7, .index_c = 2},
    {.index_a = 8, .index_b = 2, .index_c = 1},
    // top
    {.index_a = 2, .index_b = 7, .index_c = 5},
    {.index_a = 2, .index_b = 5, .index_c = 3},
    // bottom
    {.index_a = 6, .index_b = 8, .index_c = 1},
    {.index_a = 6, .index_b = 1, .index_c = 4}
};

void load_cube_mesh_data(void) {
    for (int i = 0; i < N_CUBE_VERTICES; i++) {
        vec3_t cube_vertex = cube_vertices[i];
        array_push(mesh.vertices, cube_vertex);
    }
    for (int i = 0; i < N_CUBE_FACES; i++) {
        triface_t cube_face = cube_faces[i];
        array_push(mesh.faces, cube_face);
    }
}