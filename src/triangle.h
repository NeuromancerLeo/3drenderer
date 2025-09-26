#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vector.h"

// 该结构体存储三角形面的顶点索引
typedef struct {
    int index_a;
    int index_b;
    int index_c;
} triface_t; 

// 该结构体存储 2D 三角形的顶点坐标
typedef struct {
    vec2_t points[3];
} triangle_t;

#endif