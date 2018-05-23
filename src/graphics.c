//
// Created by Firehorse on 22/05/2018.
//

#include <cglm/types.h>
#include <malloc.h>
#include "graphics.h"

shader_t create_shader(const char *vertex, const char *fragment) {
    uint program = glCreateProgram();
    uint vert_handle = glCreateShader(GL_VERTEX_SHADER);
    uint frag_handle = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vert_handle, 1, &vertex, null);
    glCompileShader(vert_handle);

    check_shader_compilation(vert_handle);

    glShaderSource(frag_handle, 1, &fragment, null);
    glCompileShader(frag_handle);

    check_shader_compilation(frag_handle);

    glAttachShader(program, vert_handle);
    glAttachShader(program, frag_handle);

    // TODO(temdisponivel): bind uniform locations

    glLinkProgram(program);

    check_program_linkage(program);

    glDeleteShader(vert_handle);
    glDeleteShader(frag_handle);

    check_gl_error();

    shader_t shader;
    shader.handle = program;
    return shader;
}

void destroy_shader(shader_t shader) {
    glDeleteProgram(shader.handle);
}

model_t create_quad() {
    vec3 *points = malloc(sizeof(vec3) * 6);

    points[0].x = -1;
    points[0].y = 0;
    points[0].z = 0;

    points[1].x = 1;
    points[1].y = 0;
    points[1].z = 0;

    points[2].x = 1;
    points[2].y = 1;
    points[2].z = 0;

    points[3].x = -1;
    points[3].y = 0;
    points[3].z = 0;

    points[4].x = -1;
    points[4].y = 1;
    points[4].z = 0;

    points[5].x = 1;
    points[5].y = 1;
    points[5].z = 0;

    model_t model;
    model.positions = points;
    return model;
}

void destroy_model(model_t model) {
    free(model.positions);
}