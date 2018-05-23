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

    CHECK_SHADER_COMPILATION(vert_handle);

    glShaderSource(frag_handle, 1, &fragment, null);
    glCompileShader(frag_handle);

    CHECK_SHADER_COMPILATION(frag_handle);

    glAttachShader(program, vert_handle);
    glAttachShader(program, frag_handle);

    glBindAttribLocation(program, VERT_POS_INDEX, "position");

    glLinkProgram(program);

    CHECK_PROGRAM_LINKAGE(program);

    glDeleteShader(vert_handle);
    glDeleteShader(frag_handle);

    CHECK_GL_ERROR();

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
    points[0].y = -1;
    points[0].z = 0;

    points[1].x = 1;
    points[1].y = -1;
    points[1].z = 0;

    points[2].x = 1;
    points[2].y = 1;
    points[2].z = 0;

    points[3].x = -1;
    points[3].y = -1;
    points[3].z = 0;

    points[4].x = -1;
    points[4].y = 1;
    points[4].z = 0;

    points[5].x = 1;
    points[5].y = 1;
    points[5].z = 0;

    model_t model;
    model.positions = points;
    model.positions_len = 6;
    model.indexes = null;
    model.indexes_len = 0;
    return model;
}

void destroy_model(model_t model) {
    free(model.positions);
}

#ifdef DEV

void print_model(model_t model) {
    for (int i = 0; i < model.positions_len; ++i) {
        vec3 pos = model.positions[i];
        printf("%f %f %f\n", pos.x, pos.y, pos.z);
    }
}

#endif

mesh_t create_mesh(model_t model) {
    uint vao;
    uint vbo;
    uint vio = 0;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(
            GL_ARRAY_BUFFER,
            sizeof(vec3) * model.positions_len,
            model.positions,
            GL_STATIC_DRAW
    );

    CHECK_GL_ERROR();

    glVertexAttribPointer(
            VERT_POS_INDEX,
            3, // Dimention (vec3)
            GL_FLOAT,
            GL_FALSE,
            0,
            0
    );

    CHECK_GL_ERROR();

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    if (model.indexes_len) {
        glGenBuffers(1, &vio);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vio);

        glBufferData(
                GL_ELEMENT_ARRAY_BUFFER,
                sizeof(uint) * model.indexes_len,
                model.indexes,
                GL_STATIC_DRAW
        );

        CHECK_GL_ERROR();

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    mesh_t mesh;
    mesh.vao = vao;
    mesh.vbo = vbo;
    mesh.vio = vio;

    if (vio) {
        mesh.elements_len = model.indexes_len;
    } else {
        mesh.elements_len = model.positions_len;
    }

    return mesh;
}

void destroy_mesh(mesh_t mesh) {

    glDeleteBuffers(1, &mesh.vbo);

    if (mesh.vio) {
        glDeleteBuffers(1, &mesh.vio);
    }

    glDeleteVertexArrays(1, &mesh.vao);

    CHECK_GL_ERROR();

    // TODO(temdisponivel): should we set these handles to invalid values?!
}

void draw_mesh(mesh_t mesh) {
    glBindVertexArray(mesh.vao);
    glEnableVertexAttribArray(VERT_POS_INDEX);

    if (mesh.vio) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vio);

        glDrawElements(GL_TRIANGLE_FAN, mesh.elements_len, GL_UNSIGNED_INT, null);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    } else {
        glDrawArrays(GL_TRIANGLE_FAN, 0, mesh.elements_len);
    }

    CHECK_GL_ERROR();

    glDisableVertexAttribArray(VERT_POS_INDEX);
    glBindVertexArray(0);
}