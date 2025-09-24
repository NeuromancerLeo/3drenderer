//vector.c
// 必须要指出的是，当考虑绕某一轴旋转时，使用左手进行参考（三根手指均需要表示指向 +），你需要将组成旋转平面的两个轴————即两根手指，分别扭动至对应 上y+ 右x+ 的形式（即手指夹（直）角要在左下方）
//创建人：Neuromancerrrrrr
//创建日期：2025/8/13

#include <math.h>
#include "vector.h"

vec3_t vec3_rotate_x(vec3_t vector, float angle) {
    vec3_t rotated_vector = {
        .x = vector.x,
        .y = vector.y * cos(angle) - vector.z * sin(angle),
        .z = vector.z * cos(angle) + vector.y * sin(angle)
    };
    
    return rotated_vector;
}

vec3_t vec3_rotate_y(vec3_t vector, float angle) {
    vec3_t rotated_vector = {
        .x = vector.x * cos(angle) + vector.z * sin(angle),
        .y = vector.y,
        .z = vector.z * cos(angle) - vector.x * sin(angle)
    };
    
    return rotated_vector;
}

vec3_t vec3_rotate_z(vec3_t vector, float angle) {
    vec3_t rotated_vector = {
        .x = vector.x * cos(angle) - vector.y * sin(angle),
        .y = vector.y * cos(angle) + vector.x * sin(angle),
        .z = vector.z
    };
    
    return rotated_vector;
}