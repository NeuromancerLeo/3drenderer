#include <point_cloud.h>



vec3_t cube_points[N_POINTS];
vec3_t arrow_points[35];
vec3_t projected_cube_points[N_POINTS];
vec3_t projected_arrow_points[35];

void loading_cube_points(void) {
    // 初始化表示 9x9x9 cube cloud 顶点数据的向量数组
    // 模型坐标系
    // From -1 to 1 (in this 9x9x9 cube)
    int point_count = 0;
    for (float x = -1; x <= 1; x += 0.25) {
        for (float y = -1; y <= 1; y += 0.25) {
            for (float z = -1; z <= 1; z += 0.25) {
                vec3_t new_point = { .x = x, .y = y, .z = z};
                cube_points[point_count++] = new_point;
            }
        }
    }
}

void loading_arrow_points(void) {
    // 初始化表示 arrow cloud 顶点数据的向量数组
    // 模型坐标系
    int _pc = 0;
    for (float x = -0.25; x <= 0.25; x += 0.25) {
        for (float y = 0; y <= 1.25; y += 0.25) {
            vec3_t new_point = { .x = x, .y = y, .z = 0};
            arrow_points[_pc++] = new_point;
        }
    }
    for (float x = -0.75; x <= 0.75; x += 0.25) {
            vec3_t new_point = { .x = x, .y = 1.5, .z = 0};
            arrow_points[_pc++] = new_point;
    }
    for (float x = -0.5; x <= 0.5; x += 0.25) {
            vec3_t new_point = { .x = x, .y = 1.75, .z = 0};
            arrow_points[_pc++] = new_point;
    }
    for (float x = -0.25; x <= 0.25; x += 0.25) {
            vec3_t new_point = { .x = x, .y = 2, .z = 0};
            arrow_points[_pc++] = new_point;
    }
    vec3_t new_point = { .x = 0, .y = 2.25, .z = 0};
    arrow_points[_pc++] = new_point;
    vec3_t new_point2 = { .x = 0, .y = 0, .z = 1}; // z+ 方向有一个点
    arrow_points[_pc++] = new_point2;
}

void update_cube_points(void) {
    // 将 cube cloud 的顶点数据进行投影处理，并存储到新的数组中去
    for (int i = 0; i < N_POINTS; i++) {
        vec3_t point = cube_points[i];

        //将顶点按照本地坐标系进行旋转
        static float _d = 0;
        point = vec3_rotate_x(point, _d);
        _d += 0.00001;

        //将顶点从模型坐标系转化为为世界坐标系
        static float _x = 0;
        static float _xx = 0;
        point.x += sin(_x) * 1.5; //在这里做出每帧移动效果，即相当于在世界坐标系移动物体
        point.y += sin(_xx) * 1.5;
        _x += 0.000001;
        _xx += 0.000003;

        //将顶点从世界坐标系转化为为相机坐标系
        point.z -= -5;
        projected_cube_points[i] = project(point);

        // printf("original: (%lf, %lf, %lf);       projected: (%lf, %lf)\n",
        //     cube_points[i].x,
        //     cube_points[i].y,
        //     cube_points[i].z,
        //     projected_cube_points[i].x,
        //     projected_cube_points[i].y
        // );
    }
}

void update_arrow_points(void) {
    // 将 arrow cloud 的顶点数据进行投影处理，并存储到新的数组中去
    for (int i = 0; i < 35; i++) {
        vec3_t point = arrow_points[i];

        //将顶点按照本地坐标系进行旋转
        static float _d = 0;
        point = vec3_rotate_z(point, _d);
        point = vec3_rotate_y(point, _d);
        _d += 0.0001;

        //将顶点转化为世界坐标系
        point.x -= 3;

        //将顶点从世界坐标系转化为为相机坐标系
        point.z -= -5;
        projected_arrow_points[i] = project(point);

        // printf("original: (%lf, %lf, %lf);       projected: (%lf, %lf)\n",
        //     cube_points[i].x,
        //     cube_points[i].y,
        //     cube_points[i].z,
        //     projected_cube_points[i].x,
        //     projected_cube_points[i].y
        // );
    }
}

void rendering_cube_points(void) {
    // Loop all projected points and render them
    for (int i = 0; i < N_POINTS; i++) {
        if (projected_cube_points[i].x != 0 && projected_cube_points[i].y != 0) {
            draw_rect(
                projected_cube_points[i].x, 
                projected_cube_points[i].y, 
                2,
                2,
                0xFF00FF00
            );
        }
    }
}

void rendering_arrow_points(void) {
    // rendering arrow cloud
    for (int i = 0; i < 35; i++) {
        if (projected_arrow_points[i].x != 0 && projected_arrow_points[i].y != 0) {
            draw_rect(
                projected_arrow_points[i].x, 
                projected_arrow_points[i].y, 
                4,
                4,
                0xFFFFFF00
            );
        }
    }
}





