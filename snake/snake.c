#include "snake/snake.h"

void draw_snake_body(void)
{
    lv_canvas_fill_bg(canvas, BACKGROUND, 255);
    for (int seg = 0; seg < snake_array_length(&snake_body); seg++)
    {
        snake_pos_t segment = snake_array_get(&snake_body, seg);
        lv_canvas_draw_rect(canvas, segment.x * 32, segment.y * 32, 32, 32, &foreground);
    }
}

void draw_fruit(void)
{
    lv_canvas_draw_rect(canvas, fruit.x * 32, fruit.y * 32, 32, 32, &fruitColor);
}

static void turn_left(lv_obj_t *btn, lv_event_t event)
{
    if (event == LV_EVENT_CLICKED)
    {
        if (direction.x != 0)
        {
            direction.y = -direction.x;
            direction.x = 0;
        }
        else
        {
            direction.x = direction.y;
            direction.y = 0;
        }
    }
}

static void turn_right(lv_obj_t *btn, lv_event_t event)
{
    if (event == LV_EVENT_CLICKED)
    {
        if (direction.x != 0)
        {
            direction.y = direction.x;
            direction.x = 0;
        }
        else
        {
            direction.x = -direction.y;
            direction.y = 0;
        }
    }
}

uint8_t check_collision(snake_pos_t pos)
{
    if (fruit.x == pos.x && fruit.y == pos.y)
    {
        return 1;
    }
    return 0;
}

uint8_t check_gameover(snake_pos_t pos)
{
    for (int i = 0; i < snake_array_length(&snake_body); i++)
    {
        snake_pos_t segment = snake_array_get(&snake_body, i);
        if (pos.x == segment.x && pos.y == segment.y)
        {
            return 1;
        }
    }
    return 0;
}

void new_fruit()
{
    int x;
    int y;
loop:
    x = rand() % 10;
    y = rand() % 10;
    for (int i = 0; i < snake_array_length(&snake_body); i++)
    {
        snake_pos_t segment = snake_array_get(&snake_body, i);
        if (x == segment.x && y == segment.y)
        {
            goto loop;
        }
    }
end:
    fruit.x = x;
    fruit.y = y;
}

void draw_score()
{
    char buffer[20];
    sprintf(buffer, "Score: %d", score);
    lv_canvas_draw_text(canvas, 0, 0, 320, &score_color, buffer, LV_LABEL_ALIGN_LEFT);
}

void run(void)
{
    snake_pos_t pos = snake_array_last(&snake_body);
    int targetX = pos.x + direction.x;
    int targetY = pos.y + direction.y;
    if (targetX == 10)
    {
        targetX = 0;
    }
    else if (targetX == -1)
    {
        targetX = 9;
    }
    if (targetY == 10)
    {
        targetY = 0;
    }
    else if (targetY == -1)
    {
        targetY = 9;
    }
    if (check_gameover((snake_pos_t){targetX, targetY}))
    {
        printf("GAME OVER\n");
        game_over = true;
        return;
    }
    if (check_collision((snake_pos_t){targetX, targetY}))
    {
        snake_array_push(&snake_body, (snake_pos_t){targetX, targetY});
        new_fruit();
        score++;
    }
    else
    {
        snake_array_push_and_shift(&snake_body, (snake_pos_t){targetX, targetY});
    }
}

void snake_task(lv_task_t *task)
{
    if (!game_over)
    {
        run();
        draw_snake_body();
        draw_fruit();
        draw_score();
    }
    else
    {
        lv_canvas_fill_bg(canvas, LV_COLOR_BLACK, 255);
        lv_canvas_draw_text(canvas, 0, 150, 320, &gameover_color, "GAME OVER", LV_LABEL_ALIGN_CENTER);
        char buffer[20];
        sprintf(buffer, "Score: %d", score);
        lv_canvas_draw_text(canvas, 0, 170, 320, &gameover_color, buffer, LV_LABEL_ALIGN_CENTER);
    }
}

static void step(lv_obj_t *btn, lv_event_t event)
{
    if (event == LV_EVENT_CLICKED)
    {
        // run();
    }
}

void snake()
{
    direction.x = 1;
    direction.y = 0;
    snake_array_init(&snake_body, 4);
    snake_array_set(&snake_body, 0, (snake_pos_t){0, 3});
    snake_array_set(&snake_body, 1, (snake_pos_t){1, 3});
    snake_array_set(&snake_body, 2, (snake_pos_t){2, 3});
    snake_array_set(&snake_body, 3, (snake_pos_t){3, 3});

    lv_draw_rect_dsc_init(&background);
    lv_draw_rect_dsc_init(&foreground);
    lv_draw_rect_dsc_init(&fruitColor);
    lv_draw_label_dsc_init(&gameover_color);
    lv_draw_label_dsc_init(&score_color);

    background.bg_color = BACKGROUND;

    foreground.bg_color = FOREGROUND;
    foreground.border_width = 1;
    foreground.border_color = LV_COLOR_BLACK;

    fruitColor.bg_color = LV_COLOR_YELLOW;
    fruitColor.border_width = 1;
    fruitColor.border_color = LV_COLOR_BLACK;

    gameover_color.color = LV_COLOR_RED;
    score_color.color = LV_COLOR_RED;

    lv_obj_t *scr = lv_scr_act();
    /**
     * Create Left Button
     */
    left_btn = lv_btn_create(scr, 0);
    lv_obj_t *left_label = lv_label_create(left_btn, 0);
    lv_label_set_text(left_label, LV_SYMBOL_LEFT);
    lv_obj_align(left_btn, scr, LV_ALIGN_IN_BOTTOM_LEFT, 0, 0);
    lv_obj_set_event_cb(left_btn, turn_left);

    /**
     * Create Right Button
     */
    right_btn = lv_btn_create(scr, 0);
    lv_obj_t *right_label = lv_label_create(right_btn, 0);
    lv_label_set_text(right_label, LV_SYMBOL_RIGHT);
    lv_obj_align(right_btn, scr, LV_ALIGN_IN_BOTTOM_RIGHT, 0, 0);
    lv_obj_set_event_cb(right_btn, turn_right);

    // lv_obj_t *step_btn = lv_btn_create(scr, 0);
    // lv_obj_t *step_label = lv_label_create(step_btn, 0);
    // lv_label_set_text(step_label, LV_SYMBOL_LOOP);
    // lv_obj_align(step_btn, scr, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
    // lv_obj_set_event_cb(step_btn, step);

    /**
     * Create Canvas
     */
    canvas = lv_canvas_create(scr, 0);
    lv_obj_set_size(canvas, 320, 320);
    lv_color_t buffer[LV_CANVAS_BUF_SIZE_TRUE_COLOR(320, 320)];
    lv_canvas_set_buffer(canvas, buffer, 320, 320, LV_IMG_CF_TRUE_COLOR);

    lv_canvas_fill_bg(canvas, BACKGROUND, 255);

    lv_task_create(snake_task, 500, 1, 0);
}

static int tick_thread(void *data)
{
    (void)data;

    while (1)
    {
        SDL_Delay(5);   /*Sleep for 5 millisecond*/
        lv_tick_inc(5); /*Tell LittelvGL that 5 milliseconds were elapsed*/
    }

    return 0;
}

static void hal_init(void)
{
    /* Use the 'monitor' driver which creates window on PC's monitor to simulate a display*/
    monitor_init();

    /*Create a display buffer*/
    static lv_disp_buf_t disp_buf1;
    static lv_color_t buf1_1[LV_HOR_RES_MAX * 120];
    lv_disp_buf_init(&disp_buf1, buf1_1, NULL, LV_HOR_RES_MAX * 120);

    /*Create a display*/
    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv); /*Basic initialization*/
    disp_drv.buffer = &disp_buf1;
    disp_drv.flush_cb = monitor_flush;
    lv_disp_drv_register(&disp_drv);

    /* Add the mouse as input device
   * Use the 'mouse' driver which reads the PC's mouse*/
    mouse_init();
    lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv); /*Basic initialization*/
    indev_drv.type = LV_INDEV_TYPE_POINTER;

    /*This function will be called periodically (by the library) to get the mouse position and state*/
    indev_drv.read_cb = mouse_read;
    lv_indev_t *mouse_indev = lv_indev_drv_register(&indev_drv);

    /* Tick init.
   * You have to call 'lv_tick_inc()' in periodically to inform LittelvGL about
   * how much time were elapsed Create an SDL thread to do this*/
    SDL_CreateThread(tick_thread, "tick", NULL);
}

int main(void)
{
    lv_init();

    hal_init();

    snake();

    while (1)
    {
        lv_task_handler();
        usleep(5 * 1000);
    }
    return 0;
}