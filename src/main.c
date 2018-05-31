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
    
    model_t quad = create_quad();
    mesh_t quad_mesh = create_mesh(&quad);
    
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
    create_camera_perspective(RAD(45), 16 / 9.f, .01f, 10000.f, &camera_2);
    camera_2.clear_depth_only = true;
    camera_2.clear_color = COLOR_MAKE_RED();
    //camera_2.transform.position.y += 3;
    
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
        draw_mesh(&quad_mesh, &material, &trans);

        use_camera(&camera_2);

        //assert(shader.handle);
        draw_mesh(&quad_mesh, &material, &trans);
        
        //glBindTexture(GL_TEXTURE_2D, 0);
        
        glfwSwapBuffers(window);
    }

    destroy_model(&quad);
    destroy_mesh(&quad_mesh);
    destroy_material(&material);

    CHECK_GL_ERROR();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}