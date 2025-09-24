//display.c
// 该项目的约定：3D 空间环境使用左手坐标系（+z 朝前，+y 朝上），屏幕空间环境使用 +y 朝下，+x 朝右
//创建人：Neuromancerrrrrr
//创建日期：2025/8/13

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "display.h"
#include "vector.h"


SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
uint32_t* color_buffer = NULL;
SDL_Texture* color_buffer_texture = NULL;

//窗口分辨率
int window_width = 1920;
int window_height = 1080;


bool initialize_window(void) {
    //Initialize the SDL Subsystems
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL.\n");
        return false;
    }

    //设置窗口分辨率为当前显示器的全屏分辨率
    //Use SDL to query what is the fullscreen max. width and height
    // SDL_DisplayMode display_mode;
    // SDL_GetCurrentDisplayMode(0, &display_mode);
    // window_width = display_mode.w;
    // window_height = display_mode.h;

    //Create a SDL window
    window = SDL_CreateWindow(
        "renderer",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        window_width,
        window_height,
        SDL_WINDOW_BORDERLESS
    );
    
    if (!window) {
        fprintf(stderr, "Error creating SDL window.\n");
        return false;
    }


    //Create a SDL renderer
    renderer = SDL_CreateRenderer(
        window,
        -1,
        0
    );

    if (!renderer) {
        fprintf(stderr, "Error creating SDL renderer.\n");
        return false;
    }

    fprintf(stdout, "Success initialized SDL window!\n");
    return true;
}


void render_color_buffer(void) {
    SDL_UpdateTexture(
        color_buffer_texture,
        NULL,
        color_buffer,
        (int) sizeof(uint32_t) * window_width
    );

    SDL_RenderCopy(
        renderer,
        color_buffer_texture,
        NULL,
        NULL
    );
}

void clear_color_buffer(uint32_t color) {
    for (int i = 0; i < window_height * window_width; i++) {
            color_buffer[i] = color;
    }
}


void draw_grid(uint32_t color) {
    // 绘制垂直线
    for (int x = 10; x < window_width; x += 10) {
        for (int y = 0; y < window_height; y++) {
            draw_pixel(x, y, color);
        }
    }
    // 绘制水平线
    for (int y = 10; y < window_height; y += 10) {
        for (int x = 0; x < window_width; x++) {
            draw_pixel(x, y, color);
        }
    }
}

void draw_pixel(unsigned x, unsigned y, uint32_t color) {
    if ((x >= 0 && x < window_width) && (y >= 0 && y < window_height)) {
        color_buffer[(window_width * y) + x] = color;
    } 
}

void draw_line(unsigned x0, unsigned y0, unsigned x1, unsigned y1, uint32_t color) {

    // 总是从 y 坐标最大的点开始绘制
    // 如果 y 坐标相同，确保从 x 坐标较小的点开始绘制
    if (y0 < y1) {
        int temp = x0;
        x0 = x1;
        x1 = temp;

        temp = y0;
        y0 = y1;
        y1 = temp;
    }
    else if (y0 == y1 && x0 > x1) {
        int temp = x0;
        x0 = x1;
        x1 = temp;

        temp = y0;
        y0 = y1;
        y1 = temp;
    }
    
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    // 步进判断
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;

    int err = dx - dy;
    int e2;

    while (1) {
        draw_pixel(x0, y0, color);
        
        if (x0 == x1 && y0 == y1) break;
        
        e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void draw_triangle(triangle_t triangle, uint32_t color) {
    draw_line(triangle.points[0].x, triangle.points[0].y, triangle.points[1].x, triangle.points[1].y, color);
    draw_line(triangle.points[0].x, triangle.points[0].y, triangle.points[2].x, triangle.points[2].y, color);
    draw_line(triangle.points[1].x, triangle.points[1].y, triangle.points[2].x, triangle.points[2].y, color);
}

void draw_rect(unsigned x, unsigned y, unsigned width, unsigned height, uint32_t color) {
    for (int i = y; i < y + height; i++) {
        for (int j = x; j < x + width && j < window_width; j++) {
            draw_pixel(j, i, color);
        }
    }
    
}

void destroy_window(void) {
    free(color_buffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}