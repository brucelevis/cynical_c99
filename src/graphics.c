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
    vertex_t *vertices = malloc(sizeof(vertex_t) * 4);

    vertices[0].position.x = -1;
    vertices[0].position.y = -1;
    vertices[0].position.z = 0;
    vertices[0].uv.x = 0;
    vertices[0].uv.y = 0;
    vertices[0].color.r = 1;
    vertices[0].color.g = 0;
    vertices[0].color.b = 0;
    vertices[0].color.a = 1;

    vertices[1].position.x = 1;
    vertices[1].position.y = -1;
    vertices[1].position.z = 0;
    vertices[1].uv.x = 1;
    vertices[1].uv.y = 0;
    vertices[1].color.r = 0;
    vertices[1].color.g = 1;
    vertices[1].color.b = 0;
    vertices[1].color.a = 1;

    vertices[2].position.x = 1;
    vertices[2].position.y = 1;
    vertices[2].position.z = 0;
    vertices[2].uv.x = 1;
    vertices[2].uv.y = 1;
    vertices[2].color.r = 0;
    vertices[2].color.g = 0;
    vertices[2].color.b = 1;
    vertices[2].color.a = 1;

    vertices[3].position.x = -1;
    vertices[3].position.y = 1;
    vertices[3].position.z = 0;
    vertices[3].uv.x = 0;
    vertices[3].uv.y = 1;
    vertices[3].color.r = 1;
    vertices[3].color.g = 1;
    vertices[3].color.b = 0;
    vertices[3].color.a = 1;

    uint *index = malloc(sizeof(uint) * 6);
    index[0] = 0;
    index[1] = 1;
    index[2] = 2;
    index[3] = 0;
    index[4] = 3;
    index[5] = 2;

    model_t model;
    model.vertices = vertices;
    model.vertices_len = 4;
    model.indexes = index;
    model.indexes_len = 6;
    return model;
}

void destroy_model(model_t model) {
    free(model.vertices);
    if (model.indexes) {
        free(model.indexes);
    }
}

#ifdef DEV

void print_model(model_t model) {
    for (int i = 0; i < model.vertices_len; ++i) {
        vertex_t vert = model.vertices[i];
        printf(
                "x: %f y: %f z: %f - r: %f g: %f b: %f a: %f - u: %f v: %f \n",
                vert.position.x, vert.position.y, vert.position.z,
                vert.color.r, vert.color.g, vert.color.b, vert.color.a,
                vert.uv.x, vert.uv.y
        );
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

    const int POS_SIZE = 3; // x, y, z
    const int UV_SIZE = 2; // u, v
    const int COLOR_SIZE = 4; // r, g, b, a

    const int VERTEX_SIZE = (POS_SIZE + UV_SIZE + COLOR_SIZE) * sizeof(float);

    const int POS_OFFSET = 0;
    const int UV_OFFSET = (POS_SIZE * sizeof(float));
    const int COLOR_OFFSET = ((POS_SIZE + UV_SIZE) * sizeof(float));

    // TODO(temdisponivel): temp alloc this
    uint all_data_size = VERTEX_SIZE * model.vertices_len;

    float *all_data = (float *) malloc(all_data_size);

    int all_data_index = 0;
    for (int i = 0; i < model.vertices_len; ++i) {
        vertex_t v = model.vertices[i];

        // Position
        all_data[all_data_index++] = v.position.x;
        all_data[all_data_index++] = v.position.y;
        all_data[all_data_index++] = v.position.z;

        // UV
        all_data[all_data_index++] = v.uv.x;
        all_data[all_data_index++] = v.uv.y;

        // Color
        all_data[all_data_index++] = v.color.r;
        all_data[all_data_index++] = v.color.g;
        all_data[all_data_index++] = v.color.b;
        all_data[all_data_index++] = v.color.a;
    }

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(
            GL_ARRAY_BUFFER,
            all_data_size,
            all_data,
            GL_STATIC_DRAW
    );
    CHECK_GL_ERROR();

    free(all_data);

    glVertexAttribPointer(
            VERT_POS_INDEX,
            POS_SIZE,
            GL_FLOAT,
            GL_FALSE,
            VERTEX_SIZE,
            (void *) POS_OFFSET
    );

    glVertexAttribPointer(
            VERT_UV_INDEX,
            UV_SIZE,
            GL_FLOAT,
            GL_FALSE,
            VERTEX_SIZE,
            (void *) UV_OFFSET
    );

    glVertexAttribPointer(
            VERT_COLOR_INDEX,
            COLOR_SIZE,
            GL_FLOAT,
            GL_FALSE,
            VERTEX_SIZE,
            (void *) COLOR_OFFSET
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
        mesh.elements_len = model.vertices_len;
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