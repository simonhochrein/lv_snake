#include "array.h"

void snake_array_init(snake_array_t *array, int length)
{
    array->length = length;
    array->items = malloc(sizeof(snake_pos_t) * length);
}
int snake_array_length(snake_array_t *array) { return array->length; }
void snake_array_set(snake_array_t *array, int index, snake_pos_t value)
{
    array->items[index].x = value.x;
    array->items[index].y = value.y;
}
snake_pos_t snake_array_get(snake_array_t *array, int index) { return array->items[index]; }

void snake_array_push_and_shift(snake_array_t *array, snake_pos_t point) {
    for(int i = 0; i < array->length; i++) {
        snake_array_set(array, i, array->items[i+1]);
    }
    snake_array_set(array, array->length-1, point);
}

void snake_array_push(snake_array_t *array, snake_pos_t point) {
    array->length++;
    array->items = realloc(array->items, sizeof(snake_pos_t) * array->length);
    snake_array_set(array, array->length-1, point);
}

snake_pos_t snake_array_last(snake_array_t *array) {
    return array->items[array->length-1];
}