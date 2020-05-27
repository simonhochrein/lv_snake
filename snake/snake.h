#ifndef _snake_h
#define _snake_h

#include "array.h"

#include "lvgl/lvgl.h"
#include "lv_drivers/display/monitor.h"

#include <SDL2/SDL.h>
#include "lv_drivers/indev/mouse.h"

#include <unistd.h>
#include <stdlib.h>

#define BACKGROUND LV_COLOR_BLUE
#define FOREGROUND LV_COLOR_RED

snake_array_t snake_body;

snake_pos_t fruit;

lv_obj_t *left_btn, *right_btn, *canvas;

lv_draw_rect_dsc_t background, foreground, fruitColor;

lv_draw_label_dsc_t gameover_color, score_color;

typedef struct {
    int x;
    int y;
} snake_delta_t;

snake_delta_t direction;

uint8_t game_over;
int score;

#endif