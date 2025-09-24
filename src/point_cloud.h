#ifndef POINT_CLOUD_H
#define POINT_CLOUD_H

#include "vector.h"

// 声明 向量/顶点 的数组
#define N_POINTS 729
extern vec3_t cube_points[N_POINTS]; // 9x9x9 cube cloud
extern vec3_t arrow_points[35]; // arrow cloud
extern vec2_t projected_cube_points[N_POINTS]; // 投影处理后的顶点数组
extern vec2_t projected_arrow_points[35];

void loading_cube_points(void);
void loading_arrow_points(void);

void update_cube_points(void);
void update_arrow_points(void);

void rendering_cube_points(void);
void rendering_arrow_points(void);

#endif