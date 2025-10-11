//main.c
// 根据古斯塔沃先生的课程“3D Computer Graphics Programming”，
// 这是一个小型的 3D 软渲染器，使用 C99 和 SDL2 库实现。
// 该项目的约定：3D 空间环境使用左手坐标系（+z 朝前，+y 朝上），屏幕空间环境使用 +y 朝下，+x 朝右
// 该文件包含程序的 main 函数入口
//创建人：Neuromancerrrrrr
//创建日期：2025/8/13


#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <SDL2\SDL.h>
#include "array.h"
#include "display.h"
#include "vector.h"
#include "mesh.h"

// _temp
////////////////////////////////////////////////////////////////////////

vec2_t project(vec3_t point);

// Array of triangles that should be rendered frame by frame
triangle_t* triangles_to_render = NULL;

// 世界空间坐标系下的相机坐标
vec3_t camera_posistion = {0, 0, -5};
float fov_factor = 640; //投影缩放因子

////////////////////////////////////////////////////////////////////////

bool is_running = false;
uint32_t previous_frame_time = 0;

void setup(void) {
    //分配内存给颜色缓冲区
    color_buffer = (uint32_t*) malloc(
        sizeof(uint32_t) * window_width * window_height
    );

    //创建用于显示颜色的 SDL texture
    color_buffer_texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        window_width,
        window_height
    );
    
    load_obj_file_data("./assets/f22.obj"); // 加载网格数据（mesh_t）
}


void process_input(void) {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            is_running = false;
            break;
        case SDL_KEYDOWN:

            //ESC 键退出程序
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                is_running = false;
            }

            break;
    }
}


// _temp
/**
 *  \brief 该函数将表示为相机空间内的顶点坐标转换（投影）为屏幕空间内的对应顶点坐标 
 * 
 *  \return a projected vector2 point. 
 * 
 *  注意：如果顶点坐标 z 分量 <= 0, 则返回 (0, 0)
 * 
**/
vec2_t project(vec3_t point) {
    if (point.z > 0){
        vec2_t projected_point = {
            // 将相机空间内的顶点坐标转换为屏幕空间内的对应顶点坐标
            .x = ((point.x * fov_factor) / point.z) + (window_width / 2),
            .y = -((point.y * fov_factor) / point.z) + (window_height / 2) //注意屏幕坐标系是 y+ 朝下，故在此进行反转
        };

        return projected_point;
    }
    else {
        //如果顶点坐标 z 分量 <= 0, 则返回 (0, 0)
        vec2_t _vec2 = {0,0};
        return _vec2;
    }
    
}

// Transformation and Projection.
void update(void) {
    // control our time step.
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - previous_frame_time);
    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
        SDL_Delay(time_to_wait);
    }
    previous_frame_time = SDL_GetTicks();
    //////////////////////////////////////////////////////////////////////////////

    // 初始化要渲染的三角形数组
    triangles_to_render = NULL;

    mesh.rotation.x += 0.005;
    mesh.rotation.y += 0.005;
    mesh.rotation.z += 0.005;

    static float _d = 0;

    // Loop all triangle faces of our mesh
    // 整个流程：利用 triface 的索引值获取面的各个顶点，进行变换、投影，
    //      处理完毕后便将顶点存入 triangles_to_render 数组中
    int num_faces = array_length(mesh.faces);
    for (int i = 0; i < num_faces; i++) {
        triface_t mesh_face = mesh.faces[i];
        
        // 使用 mesh 每个 face 的 3 个索引值作为 mesh vertices 数组的查询用下标
        // 这样就可以获取到属于 face 的各个 vertices
        vec3_t face_vertices[3];
        face_vertices[0] = mesh.vertices[mesh_face.index_a - 1];
        face_vertices[1] = mesh.vertices[mesh_face.index_b - 1];
        face_vertices[2] = mesh.vertices[mesh_face.index_c - 1];

        vec3_t transformed_vertices[3];

        // Loop all three vertices of this current face and apply transformations
        for (int j = 0; j < 3; j++) {
            vec3_t transformed_verticex;
            
            transformed_verticex = face_vertices[j];
            // 旋个转
            transformed_verticex = vec3_rotate_x(transformed_verticex, mesh.rotation.x);
            transformed_verticex = vec3_rotate_y(transformed_verticex, mesh.rotation.y);
            transformed_verticex = vec3_rotate_z(transformed_verticex, mesh.rotation.z);
            
            transformed_verticex.y += sin(_d);
            _d += 0.00001;

            // 将世界空间内的顶点坐标转换为相机（视图）空间内的顶点坐标
            transformed_verticex.z -= camera_posistion.z;

            // Save transformed vertex in the array of transformed vertices
            transformed_vertices[j] = transformed_verticex;
        }

        // 开始背面剔除检测，该项目规定顺时针顶点顺序为正面
        vec3_t vector_a = transformed_vertices[0];      /*    a    */
        vec3_t vector_b = transformed_vertices[1];      /*   / \   */
        vec3_t vector_c = transformed_vertices[2];      /*  c---b  */
        
        vec3_t vector_ab = vec3_sub(vector_b, vector_a);
        vec3_t vector_ac = vec3_sub(vector_c, vector_a);
        vec3_t normal = vec3_cross(vector_ab, vector_ac);
        // 注意！现在顶点坐标已经变换到了视图空间（View-Space）所以这里必须计算的是 to_view，而不是 to_camera（前者即为视图空间的原点坐标，后者的相机坐标处于世界空间）
        vec3_t ray_to_view = vec3_sub((vec3_t){0,0,0}, vector_a);

        float dot_normal_view = vec3_dot(vec3_normalized(normal), vec3_normalized(ray_to_view));
        
        if(dot_normal_view < 0)
        {
            continue;   // 剔除
        }

        triangle_t projected_triangle;

        // Loop all three vertices to perform projection
        for(int j = 0; j < 3; j++) {
            
            // 投影
            vec2_t projected_point = project(transformed_vertices[j]);

            // 保存
            projected_triangle.points[j] = projected_point;
        }

        // Save the projected triangle in the array of triangles to render
        array_push(triangles_to_render, projected_triangle);
    }

}


void render(void) {

    static uint32_t _color = 0xFF000000; //临时的动态颜色变量
    clear_color_buffer(_color);

    draw_grid(0xFF333333);

    int num_triangles = array_length(triangles_to_render);
    // Loop all projected triangles and render them
    for (int i = 0; i < num_triangles; i++) {
        
        triangle_t triangle = triangles_to_render[i];

        draw_triangle(triangle, 0xFF00FFFF);
    }

    // 在每一次帧循环结束后释放 triangles_to_render 数组
    array_free(triangles_to_render);

    render_color_buffer();
    
    SDL_RenderPresent(renderer);
}

// free the memory that was dynamically allocated by the program
void free_resources(void) {
    free(color_buffer);
    array_free(mesh.faces);
    array_free(mesh.vertices);
}

int main(int argc, char *argv[]) {
    
    is_running = initialize_window();

    setup();

    while (is_running) {
        process_input();
        update();
        render();
    }

    destroy_window();
    free_resources();

    fprintf(stdout, "The program exited.");
    return 0;
}
