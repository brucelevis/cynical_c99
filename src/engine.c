//
// Created by temdisponivel on 04/06/2018.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "engine.h"
#include "memory.h"
#include "graphics.h"

config_t engine_config = {};
GLFWwindow *game_window;
vec2_t screen_size;
mesh_t quad;

engine_init_status_t init_engine() {
    create_default_memory_pool();

    glfwInit();

    game_window = glfwCreateWindow(1024, 768, "Hello world!", NULL, NULL);

    if (!game_window) {
        return ENGINE_INIT_CANNOT_CREATE_WINDOW;
    }

    glfwMakeContextCurrent(game_window);

    glewInit();

    model_t quad_model = create_quad();
    quad = create_mesh(&quad_model);
    destroy_model(&quad_model);
    
    return ENGINE_INIT_OK;
}