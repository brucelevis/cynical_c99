/*
 * TODO: FIX DESTIONATION VECTORS - PASS THEM AS POINTERS
 */

#include <stdio.h>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "common.h"
#include "file.h"
#include "graphics.h"
#include "math/test.h"
#include "resources.h"
#include "engine.h"

#define CONFIG_FILE_PATH "data/config.data"

#if DEV
#include "hot_reloader.h"
#endif

// TODO(temdisponivel): Move engine related stuff into engine.c
config_t engine_config = {};


// TODO(temdisponivel): Remove me
vec2_t screen_size;
mesh_t quad;

GLFWwindow *window;

void update_engine_based_on_config() {
    glfwSetWindowSize(window, (int) engine_config.resolution.x, (int) engine_config.resolution.y);
    glfwSetWindowTitle(window, engine_config.window_title);
}

int main() {
    glfwInit();

    window = glfwCreateWindow(1024, 768, "Hello world!", NULL, NULL);
    
    if (!window) {
        return -1;
    }

    glfwMakeContextCurrent(window);

    glewInit();
    
    model_t quad_model = create_quad();
    quad = create_mesh(&quad_model);
    mesh_t quad_2 = create_mesh(&quad_model);
    
    mat4_t MVP, view, proj, view_proj, model;
    vec3_t dir, pos, up;
    
    mat4_identity(&MVP);
    mat4_identity(&view);
    mat4_identity(&proj);
    mat4_identity(&model);
    
    quat_t rot;
    vec3_t axis = VEC3_MAKE_UP();
    quat_angle_axis(&axis, RAD(0), &rot);
    
    transform_t trans = trans_make(vec3_make(0, 0, -10), vec3_make(1, 1, 1), rot);
    trans_get_mat4(&trans, &model);
    
    vec3_set(0, 0, -1, &dir);
    vec3_set(0, 0, 1, &pos);
    vec3_set(0, 1, 0, &up);
    
    mat4_look(&pos, &dir, &up, &view);
    mat4_perspective(RAD(45), 16 / 9.f, .01f, 10000.f, &proj);

    mat4_mul(&proj, &view, &view_proj);
    mat4_mul(&view_proj, &model, &MVP);
        
    material_t material;
    create_material_from_file("data/shaders/default_material.mat_def", &material);
    
    CHECK_GL_ERROR();
    
    read_config_file(CONFIG_FILE_PATH, &engine_config);
    watch_config_file(CONFIG_FILE_PATH);
    
    camera_t camera;
    create_camera_perspective(RAD(45), 16 / 9.f, .01f, 10000.f, &camera);

    camera_t camera_2;
    create_camera_orthographic(-.5f, .5f, -.5f, .5f, .01f, 10000.f, &camera_2);
    camera_2.clear_depth_only = true;
    camera_2.clear_color = COLOR_MAKE_RED();
    //camera_2.transform.position.y += 3;
    
    sprite_renderer_t renderer;
    renderer.material = material;
    renderer.size = vec2_make(600, 400);
    renderer.texel_size = .5f;
    
    while (!glfwWindowShouldClose(window)) {

#if DEV
        update_hot_reloader();
#endif

        if (engine_config.dirty) {
            update_engine_based_on_config();
            engine_config.dirty = false;
        }
        
        glfwPollEvents();

        int width, height;
        glfwGetWindowSize(window, &width, &height);
        
        screen_size.x = width;
        screen_size.y = height;
        
        glViewport(0, 0, width, height);

        use_camera(&camera);
        
        if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
            trans.position.x += 1;
        } else if (glfwGetKey(window, GLFW_KEY_LEFT)) {
            trans.position.x -= 1;
        } else if (glfwGetKey(window, GLFW_KEY_UP)) {
            camera_2.transform.position.y += 1;
        } else if (glfwGetKey(window, GLFW_KEY_DOWN)) {
            camera_2.transform.position.y -= 1;
        }

        //assert(shader.handle);
        //draw_mesh(&quad_2, &material, &trans);
        draw_sprite_renderer(&renderer, &trans);

        use_camera(&camera_2);

        //assert(shader.handle);
        //draw_mesh(&quad_2, &material, &trans);
        draw_sprite_renderer(&renderer, &trans);
        
        //glBindTexture(GL_TEXTURE_2D, 0);
        
        glfwSwapBuffers(window);
    }

    destroy_model(&quad_model);
    destroy_mesh(&quad);
    destroy_material(&material);

    CHECK_GL_ERROR();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}