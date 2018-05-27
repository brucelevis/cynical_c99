/*
 * TODO: FIX DESTIONATION VECTORS - PASS THEM AS POINTERS
 */

#include <stdio.h>
#include "GL/glew.h"
#include "GL/GL.h"
#include "GLFW/glfw3.h"
#include "common.h"
#include "file.h"
#include "graphics.h"
#include "math/maths.h"
#include "math/test.h"

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
    file_status_t result = read_file_string(
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
    result = read_file_string(
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
    
    glUseProgram(shader.handle);
    int loc = glGetUniformLocation(shader.handle, "MVP");
    glUniformMatrix4fv(loc, 1, GL_FALSE, &MVP);
    CHECK_GL_ERROR();
    
    image_t img;
    if (!load_image("data/textures/witness.jpg", &img)) {
        return -100;
    }

    texture_t tex = create_texture(&img);

    int main_texture_loc = glGetUniformLocation(shader.handle, "main_texture");
    int bump_map_loc = glGetUniformLocation(shader.handle, "bump_map_texture");
    
    texture_uniform_definition_t tex_definitions[1];
    tex_definitions[0].image_file_name = "data/textures/witness.jpg";
    tex_definitions[0].uniform_name = "main_texture";
    
    float_uniform_definition_t float_uniforms[1];
    float_uniforms[0].uniform_name = "float_value";
    float_uniforms[0].default_value = 5;

    mat4_uniform_definition_t mat4_uniforms[1];
    mat4_uniforms[0].uniform_name = "MVP";
    mat4_uniforms[0].default_value = MVP;
    
    material_definition_t definition;
    definition.vertex_shader_file = "data/shaders/default_vert.glsl";
    definition.fragment_shader_file = "data/shaders/default_frag.glsl";
    
    definition.textures_len = 1;
    definition.textures = (texture_uniform_definition_t*) tex_definitions;
    
    definition.floats_len = 1;
    definition.floats = (float_uniform_definition_t *) float_uniforms;

    definition.mat4s_len = 1;
    definition.mat4s = (mat4_uniform_definition_t *) mat4_uniforms;
    
    material_t material = create_material(&definition);
    
    CHECK_GL_ERROR();
    
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        int width, height;
        glfwGetWindowSize(window, &width, &height);
        glViewport(0, 0, width, height);

        glClearColor(0, 0, 0, 255);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        use_material(&material);
        
        //assert(shader.handle);
        draw_mesh(quad_mesh);
        
        //glBindTexture(GL_TEXTURE_2D, 0);
        
        glfwSwapBuffers(window);
    }

    destroy_shader(shader);
    destroy_model(quad);
    destroy_mesh(quad_mesh);
    destroy_image(&img);
    destroy_texture(&tex);
    destroy_material(&material);

    CHECK_GL_ERROR();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}