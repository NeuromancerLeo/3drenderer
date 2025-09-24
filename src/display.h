#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2\SDL.h>
#include "triangle.h"

#define TARGET_FPS 500
#define FRAME_TARGET_TIME (1000 / TARGET_FPS) //每帧需花费毫秒时间

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern uint32_t* color_buffer;
extern SDL_Texture* color_buffer_texture;

//窗口分辨率
extern int window_width;
extern int window_height;

bool initialize_window(void);


/**
 *  \brief 该函数将我们的 color_buffer 写入 SDL texture，并以此更新 renderer
**/
void render_color_buffer(void);

/**
 *  \brief 使用指定的颜色值清除（覆写）颜色缓冲区.
 *
 *  \param color The clear color. ARGB8888
 */
void clear_color_buffer(uint32_t color);

/**
 *  \brief 该函数使用指定的颜色值将一个背景网格图写入颜色缓冲区.
 * 
 */
void draw_grid(uint32_t color);

/**
 *  \brief 该函数使用指定的颜色值以单个像素的形式写入颜色缓冲区
 * 
 *  \param x 像素在窗口内的 x 坐标
 *  \param y 像素在窗口内的 y 坐标
 */
void draw_pixel(unsigned x, unsigned y, uint32_t color);

/**
 *  \brief 使用 Bresenham's Line Algorithm 进行给定两个像素坐标的画线
 */
void draw_line(unsigned x0, unsigned y0, unsigned x1, unsigned y1, uint32_t color);

void draw_triangle(triangle_t triangle, uint32_t color);

/**
 *  \brief 该函数使用指定的颜色值将一个实心矩形写入颜色缓冲区
 * 
 *  \param x 矩形在窗口内的 x 坐标
 *  \param y 矩形在窗口内的 y 坐标
 *  \param width 矩形宽度
 *  \param height 矩形高度
 *  \param color 填充矩形的颜色
 */
void draw_rect(unsigned x, unsigned y, unsigned width, unsigned height, uint32_t color);





void destroy_window(void);

#endif