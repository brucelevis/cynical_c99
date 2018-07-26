//
// Created by temdisponivel on 04/06/2018.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "engine.h"
#include "memory.h"
#include "graphics.h"
#include "input.h"
#include "text.h"
#include "resource_manager.h"

#define TEMP_MEM_POOL_SIZE KILO_BYTE(16)

config_t engine_config = {};
GLFWwindow *game_window;
vec2_t screen_size;
mesh_t quad;
float delta_time;
vec2_t screen_size;
float aspect_ratio;

// NOTE(temdisponivel): Maybe these are temporary, we'll see
material_t *default_text_material;
font_t default_font;
static double end_time;

void glfw_error_callback(int error_code, const char *message) {
    should_quit = true;
    ERROR(message);
}

INLINE void update_screen_size() {
    // NOTE(temdisponivel): This will actually not be needed, because the game_window will not be resizable through operational system, only inside the game
    int width, height;
    glfwGetWindowSize(game_window, &width, &height);

    screen_size.width = width;
    screen_size.height = height;

    aspect_ratio = screen_size.width / screen_size.height;    
}

engine_init_status_t init_engine() {

    make_pool(&__temp_mem_pool, TEMP_MEMORY_SIZE);

    glfwSetErrorCallback(&glfw_error_callback);
    
    glfwInit();

    game_window = glfwCreateWindow(1600, 1024, "Hello world!", NULL, NULL);

    if (game_window == NULL) {
        return ENGINE_INIT_CANNOT_CREATE_WINDOW;
    }

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
    
    default_text_material = get_material_resource("data/shaders/default_text_renderer.mat_def");
    load_font("data/fonts/arial.ttf", 64, default_text_material, &default_font);

    update_screen_size();
    
    return ENGINE_INIT_OK;
}

void start_frame() {
    // NOTE(temdisponivel): Maybe we should not clear the screen here. Maybe the game wants to use the color buffer from the previous frame or something. This basically overrides the depth-only property of cameras!
    
    clear_pool(&__temp_mem_pool);

    update_screen_size();
    
    // Clear the whole screen before using any camera
    glScissor(0, 0, screen_size.width, screen_size.height);
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    
    current_time = (float) glfwGetTime();

    update_input();

    should_quit = (bool) glfwWindowShouldClose(game_window);
}

void end_frame() {
    glfwSwapBuffers(game_window);
    
    end_time = glfwGetTime();    
    delta_time = (float) (end_time - current_time);
}