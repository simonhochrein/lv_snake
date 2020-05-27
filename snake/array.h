#ifndef _array_h
#define _array_h

#include <stdlib.h>
#include <stdint.h>

typedef struct
{
    uint8_t x;
    uint8_t y;
} snake_pos_t;

typedef struct
{
    snake_pos_t *items;
    int length;
} snake_array_t;
void snake_array_init(snake_array_t *array, int length);
int snake_array_length(snake_array_t *array);
void snake_array_set(snake_array_t *array, int index, snake_pos_t value);
snake_pos_t snake_array_get(snake_array_t *array, int index);
void snake_array_push_and_shift(snake_array_t *array, snake_pos_t point);
void snake_array_push(snake_array_t *array, snake_pos_t point);
snake_pos_t snake_array_last(snake_array_t *array);

#endif