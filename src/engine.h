//
// Created by temdisponivel on 27/05/2018.
//

#ifndef RAW_GL_ENGINE_H
#define RAW_GL_ENGINE_H

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "math/maths.h"
#include "graphics.h"

typedef struct config {
    vec2_t resolution;    
    char window_title[DEFAULT_NAME_LEN];
    bool dirty;
} config_t;

typedef enum engine_init_status {
    ENGINE_INIT_OK,
    ENGINE_INIT_CANNOT_CREATE_WINDOW,
} engine_init_status_t;

// TODO(temdisponivel): Make this NOT extern
extern config_t engine_config;
GLFWwindow *game_window;
mesh_t quad;
float delta_time;
vec2_t screen_size;
float aspect_ratio;
bool should_quit;

engine_init_status_t init_engine();

void start_frame();
void end_frame();

#endif //RAW_GL_ENGINE_H
