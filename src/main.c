/*
 * TODO: FIX DESTIONATION VECTORS - PASS THEM AS POINTERS
 */

#include <stdio.h>
#include <cglm/types.h>
#include "GL/glew.h"
#include "GL/GL.h"
#include "GLFW/glfw3.h"
#include "common.h"
#include "file.h"
#include "graphics.h"
#include "math/maths.h"

#define FILE_BUFFER_SIZE 2048
byte FILE_BUFFER[FILE_BUFFER_SIZE];

int main() {
    glfwInit();

    GLFWwindow *window = glfwCreateWindow(1024, 768, "Hello world!", NULL, NULL);

    if (!window) {
        return -1;
    }

    glfwMakeContextCurrent(window);

    glewInit();

    char *vert_shader = FILE_BUFFER;
    uint len;
    file_status_t result = read_file_data(
            "data/shaders/default_vert.glsl",
            vert_shader,
            FILE_BUFFER_SIZE,
            &len
    );

    if (result != FILE_OK) {
        ERROR("File not found!\n");
        return -1;
    }

    char *frag_shader = FILE_BUFFER + len;
    result = read_file_data(
            "data/shaders/default_frag.glsl",
            frag_shader,
            FILE_BUFFER_SIZE,
            &len
    );

    if (result != FILE_OK) {
        ERROR("File not found!\n");
        return -1;
    }

    shader_t shader = create_shader(vert_shader, frag_shader);
    model_t quad = create_quad();
    mesh_t quad_mesh = create_mesh(quad);
    
    mat4 MVP, view, proj, model;
    vec3 dir, center, up;
    
    mat4_identity(MVP);
    glm_mat4_identity(view);
    glm_mat4_identity(proj);
    glm_mat4_identity(model);
    
    make_vec3(0, 0, -1, dir);
    make_vec3(0, 0, 10, center);
    make_vec3(0, 1, 0, up);
    
    glm_lookat(center, dir, up, &view);
    glm_perspective(glm_rad(45), 16 / 9.f, .001, 10000, &proj);
    
    //glm_mat4_mul(&view, &proj, &MVP);
    
    print_model(quad);

    glUseProgram(shader.handle);
    CHECK_GL_ERROR();

        printf("x: %f y: %f z: %f w: %f\n", 
               MVP.data[0].x, MVP.data[0].y, MVP.data[0].z, MVP.data[0].w
        );

        printf("x: %f y: %f z: %f w: %f\n",
               MVP.data[1].x, MVP.data[1].y, MVP.data[1].z, MVP.data[1].w
        );

        printf("x: %f y: %f z: %f w: %f\n",
               MVP.data[2].x, MVP.data[2].y, MVP.data[2].z, MVP.data[2].w
        );

        printf("x: %f y: %f z: %f w: %f\n",
               MVP.data[3].x, MVP.data[3].y, MVP.data[3].z, MVP.data[3].w
        );

    int loc = glGetUniformLocation(shader.handle, "MVP");
    glUniformMatrix4fv(loc, 1, GL_FALSE, MVP.data->data);
    CHECK_GL_ERROR();

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        int width, height;
        glfwGetWindowSize(window, &width, &height);
        glViewport(0, 0, width, height);

        glClearColor(0, 0, 0, 255);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        draw_mesh(quad_mesh);

        glfwSwapBuffers(window);
    }

    destroy_shader(shader);
    destroy_model(quad);
    destroy_mesh(quad_mesh);

    CHECK_GL_ERROR();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}