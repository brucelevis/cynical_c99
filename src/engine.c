//
// Created by temdisponivel on 04/06/2018.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "engine.h"
#include "memory.h"
#include "graphics.h"
#include "input.h"

config_t engine_config = {};
GLFWwindow *game_window;
vec2_t screen_size;
mesh_t quad;
float delta_time;
vec2_t screen_size;
float aspect_ratio;

static double end_time;

INLINE void update_screen_size() {
    // NOTE(temdisponivel): This will actually not be needed, because the game_window will not be resizable through operational system, only inside the game
    int width, height;
    glfwGetWindowSize(game_window, &width, &height);

    screen_size.width = width;
    screen_size.height = height;

    aspect_ratio = screen_size.width / screen_size.height;    
}

engine_init_status_t init_engine() {
    create_default_memory_pool();

    glfwInit();

    game_window = glfwCreateWindow(1600, 1024, "Hello world!", NULL, NULL);

    if (!game_window) {
        return ENGINE_INIT_CANNOT_CREATE_WINDOW;
    }

    update_screen_size();

    glfwMakeContextCurrent(game_window);

    glewInit();

    model_t quad_model = create_quad();
    quad = create_mesh(&quad_model);
    destroy_model(&quad_model);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glEnable(GL_SCISSOR_TEST);
        
    // Disable V-Sync
    glfwSwapInterval(0);
    
     // TODO(temdisponivel): Create the ability to enable/disable depth test
    
    return ENGINE_INIT_OK;
}

void start_frame() {
    // NOTE(temdisponivel): Maybe we should not clear the screen here. Maybe the game wants to use the color buffer from the previous frame or something. This basically overrides the depth-only property of cameras!
    
    // Clear the whole screen before using any camera
    glScissor(0, 0, screen_size.width, screen_size.height);
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    
    current_time = (float) glfwGetTime();

    update_screen_size();

    update_input();

    should_quit = (bool) glfwWindowShouldClose(game_window);
}

void end_frame() {
    glfwSwapBuffers(game_window);
    
    end_time = glfwGetTime();    
    delta_time = (float) (end_time - current_time);
}