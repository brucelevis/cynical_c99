//
// Created by Firehorse on 22/05/2018.
//

#ifndef RAW_GL_GRAPHICS_H
#define RAW_GL_GRAPHICS_H

#include "GL/glew.h"
#include "common.h"
#include "math/maths.h"
#include <mem.h>
#include "stb_image.h"
#include "file.h"

#define VERT_POS_NAME "position"
#define VERT_UV_NAME "uv"
#define VERT_COLOR_NAME "color"

#define VERT_POS_INDEX 0
#define VERT_UV_INDEX 1
#define VERT_COLOR_INDEX 2

#define POS_DIMENTION 3 // x, y, z
#define UV_DIMENTION 2 // u, v
#define COLOR_DIMENTION 4 // r, g, b, a

#define FULL_MODEL_BYTE_SIZE(vertice_count) FULL_VERTEX_SIZE * vertice_count
#define FULL_VERTEX_SIZE ((POS_DIMENTION + UV_DIMENTION + COLOR_DIMENTION) * sizeof(float))

#define POS_BYTE_OFFSET(vertice_count) 0
#define UV_BYTE_OFFSET(vertice_count) (POS_DIMENTION * (vertice_count) * sizeof(float))
#define COLOR_BYTE_OFFSET(vertice_count) ((POS_DIMENTION + UV_DIMENTION) * (vertice_count) * sizeof(float))

typedef struct model {
    float *full_vertices_data;
    vec3_t *positions_ptr_offset;
    vec2_t *uvs_ptr_offset;
    vec4_t *colors_ptr_offset;

    uint vertices_count;

    uint *indexes;
    uint indexes_count;
} model_t;

typedef struct mesh {
    uint vao;
    uint vbo;
    uint vio;
    uint elements_len;
} mesh_t;

typedef struct shader {
    uint handle;
} shader_t;

/*
typedef enum uniform_type {
    FLOAT = 1,
    VEC2 = 2,
    VEC3 = 3,
    VEC4 = 4,
    COLOR = VEC4,
    MAT4 = 5,
    TEXTURE = 6
} uniform_type_t;

typedef struct uniform {
    int location;
    char *name;
    uniform_type_t type;
} uniform_t;

typedef struct material {
    uniform_t *uniforms;
    uint uniforms_len;
    shader_t shader;
} material_t;
*/

typedef struct image {
    vec2_t size;
    byte *data;
} image_t;

typedef struct texture {
    uint handle;
} texture_t;

shader_t create_shader(const char *vertex, const char *fragment);
void destroy_shader(shader_t shader);

model_t create_quad();
void destroy_model(model_t model);

mesh_t create_mesh(model_t model);
void destroy_mesh(mesh_t mesh);
void draw_mesh(mesh_t mesh);

bool load_image(const char *image_file, image_t *dest);
void destroy_image(const image_t *image);

texture_t create_texture(const image_t *image);
void destroy_texture(const texture_t *texture);

#ifdef DEV

void print_model(model_t model);

#endif

#define CHECK_SHADER_COMPILATION(shader) {\
    int compiled;\
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);\
    if (!compiled) {\
        int len;\
        CREATE_TEMP_STR_BUFFER();\
        glGetShaderInfoLog(shader, TEMP_STR_BUFFER_LEN, &len, TEMP_BUFFER);\
        ERROR(TEMP_BUFFER);\
    }\
}\

#define CHECK_PROGRAM_LINKAGE(program) {\
    int compiled;\
    glGetProgramiv(program, GL_LINK_STATUS, &compiled);\
    if (!compiled) {\
        int len;\
        CREATE_TEMP_STR_BUFFER();\
        glGetProgramInfoLog(program, TEMP_STR_BUFFER_LEN, &len, TEMP_BUFFER);\
        ERROR(TEMP_BUFFER);\
    }\
}\

#define CHECK_GL_ERROR() {\
    GLenum error = glGetError();\
    if (error != GL_NO_ERROR) {\
        CREATE_TEMP_STR_BUFFER();\
        sprintf(TEMP_BUFFER, "OpenGL error: '%i'\n", error);\
        ERROR(TEMP_BUFFER);\
    }\
}\

#endif //RAW_GL_GRAPHICS_H