//vector.c
// 必须要指出的是，当考虑绕某一轴旋转时，使用左手进行参考（三根手指均需要表示指向 +），你需要将组成旋转平面的两个轴————即两根手指，分别扭动至对应 上y+ 右x+ 的形式（即手指夹（直）角要在左下方）
//创建人：Neuromancerrrrrr
//创建日期：2025/8/13

#include <math.h>
#include "vector.h"

float vec2_length(vec2_t v) {
    return sqrt(v.x * v.x + v.y * v.y);
}

vec2_t vec2_normalized(vec2_t v) {
    float length = vec2_length(v);
    if(length) {
        return (vec2_t){
            v.x / length, v.y / length
        };
    }
    return (vec2_t){0, 0};
}

vec2_t vec2_add(vec2_t left, vec2_t right) {
    return (vec2_t){
        .x = left.x + right.x,
        .y = left.y + right.y,
    };
}

vec2_t vec2_sub(vec2_t left, vec2_t right) {
    return (vec2_t){
        .x = left.x - right.x,
        .y = left.y - right.y,
    };
}

vec2_t vec2_mul(vec2_t v, float factor) {
    return (vec2_t){
        .x = v.x * factor,
        .y = v.y * factor
    };
}

vec2_t vec2_div(vec2_t v, float factor) {
    return (vec2_t){
        .x = v.x / factor,
        .y = v.y / factor
    };
}

float vec2_dot(vec2_t left, vec2_t right) {
    return left.x * right.x + left.y * right.y;
}



float vec3_length(vec3_t v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

vec3_t vec3_normalized(vec3_t v) {
    float length = vec3_length(v);
    if(length) {
        return (vec3_t){
            v.x / length, v.y / length, v.z / length
        };
    }
    return (vec3_t){0, 0, 0};
}

vec3_t vec3_add(vec3_t left, vec3_t right) {
    return (vec3_t){
        left.x + right.x, left.y + right.y, left.z + right.z
    };
}

vec3_t vec3_sub(vec3_t left, vec3_t right) {
    return (vec3_t){
        left.x - right.x, left.y - right.y, left.z - right.z
    };
}

vec3_t vec3_mul(vec3_t v, float factor) {
    return (vec3_t){
        v.x * factor, v.y * factor, v.z * factor
    };
}

vec3_t vec3_div(vec3_t v, float factor) {
    return (vec3_t){
        v.x / factor, v.y / factor, v.z / factor
    };
}

float vec3_dot(vec3_t left, vec3_t right) {
    return left.x * right.x + left.y * right.y + left.z * right.z;
}

vec3_t vec3_cross(vec3_t left, vec3_t right) {
    return (vec3_t){
        .x = left.y * right.z - left.z * right.y,
        .y = left.z * right.x - left.x * right.z,
        .z = left.x * right.y - left.y * right.x,
    };
}


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