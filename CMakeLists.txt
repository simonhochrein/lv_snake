cmake_minimum_required(VERSION 3.17)
project(Snake)

file(GLOB lvgl lvgl/src/**/*.c lv_drivers/**/*.c)

include_directories(. /usr/local/include)

set(CMAKE_BUILD_TYPE Debug)

add_executable(snake snake/snake.c snake/array.c ${lvgl})
target_link_directories(snake PUBLIC /usr/local/opt/sdl2/lib)

target_link_libraries(snake SDL2)