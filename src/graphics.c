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

    glBindAttribLocation(program, VERT_POS_INDEX, VERT_POS_NAME);
    glBindAttribLocation(program, VERT_UV_INDEX, VERT_UV_NAME);
    glBindAttribLocation(program, VERT_COLOR_INDEX, VERT_COLOR_NAME);

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
    const int QUAD_VERT_COUNT = 4;
    const int QUAD_INDEX_COUNT = 6;

    float *vertices = malloc(FULL_MODEL_BYTE_SIZE(QUAD_VERT_COUNT));

    vec3 *positions = (vec3 *) vertices;
    vec2 *uvs = (vec2 *) (((void *) positions) + UV_BYTE_OFFSET(4));
    vec4 *colors = (vec4 *) (((void *) positions) + COLOR_BYTE_OFFSET(4));

    positions[0][0] = -1;
    positions[0][1] = -1;
    positions[0][2] = 0;
    uvs[0][0] = 0;
    uvs[0][1] = 0;
    colors[0][0] = 1;
    colors[0][1] = 0;
    colors[0][2] = 0;
    colors[0][3] = 1;

    positions[1][0] = 1;
    positions[1][1] = -1;
    positions[1][2] = 0;
    uvs[1][0] = 1;
    uvs[1][1] = 0;
    colors[1][0] = 0;
    colors[1][1] = 1;
    colors[1][2] = 0;
    colors[1][3] = 1;

    positions[2][0] = 1;
    positions[2][1] = 1;
    positions[2][2] = 0;
    uvs[2][0] = 1;
    uvs[2][1] = 1;
    colors[2][0] = 0;
    colors[2][1] = 0;
    colors[2][2] = 1;
    colors[2][3] = 1;

    positions[3][0] = -1;
    positions[3][1] = 1;
    positions[3][2] = 0;
    uvs[3][0] = 0;
    uvs[3][1] = 1;
    colors[3][0] = 1;
    colors[3][1] = 1;
    colors[3][2] = 0;
    colors[3][3] = 1;

    uint *index = malloc(sizeof(uint) * QUAD_INDEX_COUNT);
    index[0] = 0;
    index[1] = 1;
    index[2] = 2;
    index[3] = 0;
    index[4] = 3;
    index[5] = 2;

    model_t model;
    model.full_vertices_data = vertices;
    model.positions_ptr_offset = positions;
    model.uvs_ptr_offset = uvs;
    model.colors_ptr_offset = colors;
    model.vertices_count = QUAD_VERT_COUNT;
    model.indexes = index;
    model.indexes_count = QUAD_INDEX_COUNT;
    return model;
}

void destroy_model(model_t model) {
    free(model.full_vertices_data);
    if (model.indexes) {
        free(model.indexes);
    }
}

#ifdef DEV

void print_model(model_t model) {

    for (int i = 0; i < model.vertices_count; ++i) {
        vec3 a = model.positions_ptr_offset[i];
        vec3 pos = ;
        vec3 uv = model.uvs_ptr_offset[i];
        vec3 color = model.colors_ptr_offset[i];

        printf(
                "x: %f y: %f z: %f - r: %f g: %f b: %f a: %f - u: %f v: %f \n",
                x(pos), y(pos), z(pos),
                r(color), g(color), b(color), a(color),
                x(uv), y(uv)
        );
    }
}

#endif

mesh_t create_mesh(model_t model) {
    uint vao;
    uint vbo;
    uint vio = 0;

    const int full_model_size = FULL_MODEL_BYTE_SIZE(model.vertices_count);
    const int pos_offset = POS_BYTE_OFFSET(model.vertices_count);
    const int uv_offset = UV_BYTE_OFFSET(model.vertices_count);
    const int color_offset = COLOR_BYTE_OFFSET(model.vertices_count);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(
            GL_ARRAY_BUFFER,
            full_model_size,
            model.full_vertices_data,
            GL_STATIC_DRAW
    );
    CHECK_GL_ERROR();

    glVertexAttribPointer(
            VERT_POS_INDEX,
            POS_DIMENTION,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void *) pos_offset
    );

    glVertexAttribPointer(
            VERT_UV_INDEX,
            UV_DIMENTION,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void *) uv_offset
    );

    glVertexAttribPointer(
            VERT_COLOR_INDEX,
            COLOR_DIMENTION,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void *) color_offset
    );
    CHECK_GL_ERROR();

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    if (model.indexes_count) {
        glGenBuffers(1, &vio);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vio);

        glBufferData(
                GL_ELEMENT_ARRAY_BUFFER,
                sizeof(uint) * model.indexes_count,
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
        mesh.elements_len = model.indexes_count;
    } else {
        mesh.elements_len = model.vertices_count;
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
    glEnableVertexAttribArray(VERT_UV_INDEX);
    glEnableVertexAttribArray(VERT_COLOR_INDEX);

    if (mesh.vio) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vio);

        glDrawElements(GL_TRIANGLE_FAN, mesh.elements_len, GL_UNSIGNED_INT, null);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    } else {
        glDrawArrays(GL_TRIANGLE_FAN, 0, mesh.elements_len);
    }

    CHECK_GL_ERROR();

    glDisableVertexAttribArray(VERT_COLOR_INDEX);
    glDisableVertexAttribArray(VERT_UV_INDEX);
    glDisableVertexAttribArray(VERT_POS_INDEX);
    glBindVertexArray(0);
}