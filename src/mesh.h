#ifndef MESH_H
#define MESH_H

#include "vector.h"
#include "triangle.h"


#define N_CUBE_VERTICES 8
#define N_CUBE_FACES (6 * 2) // 立方体有 6 个面，每个面两个三角形
extern vec3_t cube_vertices[N_CUBE_VERTICES]; 
extern triface_t cube_faces[N_CUBE_FACES];

typedef struct {
    vec3_t* vertices;   // 动态 顶点 数组
    triface_t* faces;  // 动态 三角形面顶点索引 数组
    vec3_t rotation;
} mesh_t;

extern mesh_t mesh;

void load_cube_mesh_data(void);

#endif