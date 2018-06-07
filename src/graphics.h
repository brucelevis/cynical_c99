//
// Created by Firehorse on 22/05/2018.
//

#ifndef RAW_GL_GRAPHICS_H
#define RAW_GL_GRAPHICS_H

#include "GL/glew.h"
#include "math/maths.h"

#define MVP_UNI_NAME "MVP"

#define VERT_POS_NAME "position"
#define VERT_UV_NAME "uv"
#define VERT_COLOR_NAME "color"

#define SPRITE_OFFSET_UNI_NAME "sprite_offset"
#define SPRITE_SIZE_UNI_NAME "sprite_size"
#define MAIN_TEX_UNI_NAME "main_texture"

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

#define MAX_TEXTURES 10
#define MAX_IMAGES MAX_TEXTURES
#define MAX_FLOATS 5
#define MAX_MAT4S 5
#define MAX_VEC2S 5

#define DEFAULT_IMAGE_FILE_PATH "data/textures/default.png"

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

typedef struct image {
    char file_path[DEFAULT_FILE_NAME_LEN];
    vec2_t size;
    byte *data;
} image_t;

typedef enum texture_unit {
    TEXTURE_UNIT_0 = GL_TEXTURE0,
    TEXTURE_UNIT_1 = GL_TEXTURE1,
    TEXTURE_UNIT_2 = GL_TEXTURE2,
    TEXTURE_UNIT_3 = GL_TEXTURE3,
    TEXTURE_UNIT_4 = GL_TEXTURE4,
} texture_unit_t;

// TODO(temdisponivel): Make textures be referenced by pointers
typedef struct texture {
    uint handle;
    float texel_size;
    vec2_t size;
} texture_t;

typedef struct uniform_info {
    // TODO(temdisponivel): Cache the locations - make sure it works with hot reloading
    // it must recache location of the uniform after rebuild the shader
    char name[DEFAULT_NAME_LEN];
    
    int hashed_name;
} uniform_info_t;

typedef struct float_uniform {
    uniform_info_t info;
    float value;
} float_uniform_t;

typedef struct mat4_uniform {
    uniform_info_t info;
    mat4_t value;
} mat4_uniform_t;

typedef struct texture_uniform {
    uniform_info_t info;
    const texture_t *texture;
    texture_unit_t texture_unit;
} texture_uniform_t;

typedef struct vec2_uniform {
    uniform_info_t info;
    vec2_t value;
} vec2_uniform_t;

// TODO(temdisponivel): Make everyone that used material actually reference it through pointers instead of copies - necessary because of hot reloadign
typedef struct material {
    const shader_t *shader;
    
    texture_uniform_t texture_uniforms[MAX_TEXTURES];
    uint texture_uniforms_len;

    float_uniform_t float_uniforms[MAX_FLOATS];
    uint float_uniforms_len;

    mat4_uniform_t mat4_uniforms[MAX_MAT4S];
    uint mat4_uniforms_len;

    vec2_uniform_t vec2_uniforms[MAX_VEC2S];
    uint vec2_uniforms_len;
} material_t;

typedef struct float_uniform_definition {
    char uniform_name[DEFAULT_NAME_LEN];
    float default_value;
} float_uniform_definition_t;

typedef struct mat4_uniform_definition {
    char uniform_name[DEFAULT_NAME_LEN];
    mat4_t default_value;
} mat4_uniform_definition_t;

typedef struct texture_uniform_definition {
    char uniform_name[DEFAULT_NAME_LEN];
    char image_file_name[DEFAULT_FILE_NAME_LEN];
} texture_uniform_definition_t; 

typedef struct vec2_uniform_definition {
    char uniform_name[DEFAULT_NAME_LEN];
    vec2_t default_value;
} vec2_uniform_definition_t;

typedef struct material_definition {
    char shader_file[DEFAULT_FILE_NAME_LEN];
    
    texture_uniform_definition_t textures[MAX_TEXTURES];
    uint textures_len;
    
    float_uniform_definition_t floats[MAX_FLOATS];
    uint floats_len;

    mat4_uniform_definition_t mat4s[MAX_MAT4S];
    uint mat4s_len;

    vec2_uniform_definition_t vec2s[MAX_VEC2S];
    uint vec2s_len;
} material_definition_t;

typedef struct camera_t {
    mat4_t projection_matrix;    
    transform_t transform;
    
    bool clear_depth_only;
    color_t clear_color;
    int depth;
} camera_t;

typedef struct texture_renderer {
    const texture_t *texture;
    rect_t texture_area;
    vec2_t size;
    vec2_t pivot;
    const material_t *material;
} texture_renderer_t;

void reload_shader_sources(
        uint handle, 
        const char *shader_file,
        char *both_include_file_path,
        char *vert_include_file_path,
        char *frag_include_file_path
);

void update_shader_program(uint program, const char *vertex, const char *fragment);
void destroy_shader(const shader_t *shader);

model_t create_quad();
void destroy_model(const model_t *model);

mesh_t create_mesh(const model_t *model);
void destroy_mesh(const mesh_t *mesh);
void draw_mesh(const mesh_t *mesh, const material_t *material, const transform_t *trans);

void create_texture(const image_t *image, texture_t *dest);
void reload_texture(uint handle, const char *file_path);
void update_texture_data(uint handle, const image_t *image);
void destroy_texture(const texture_t *texture);

void reload_material(const char *file_path, material_t *dest);
void create_material(const material_definition_t *definition, material_t *dest);
void destroy_material(const material_t *material);

void set_texture_uniform(const material_t *material, const char *uniform_name, const texture_t *texture);
void set_float_uniform(const material_t *material, const char *uniform_name, float value);
void set_mat4_uniform(const material_t *material, const char *uniform_name, const mat4_t *value);
void set_vec2_uniform(const material_t *material, const char *uniform_name, vec2_t value);

void use_material(const material_t *material);

void create_camera_orthographic_default(float aspect_ratio, camera_t *dest);
void create_camera_orthographic(float left, float right, float bottom, float top, float near_plane, float far_plane, camera_t *dest);

void create_camera_perspective_default(float aspect_ratio, camera_t *dest);
void create_camera_perspective(float fov, float ratio, float near_plane, float far_plane, camera_t *dest);

void use_camera(const camera_t *camera);

void create_texture_renderer(const texture_t *texture, const material_t *material, texture_renderer_t *dest);
void draw_texture_renderer(const texture_renderer_t *renderer, const transform_t *trans);

#ifdef DEV

void print_model(model_t model);

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


#else

#define CHECK_SHADER_COMPILATION(shader) 

#define CHECK_PROGRAM_LINKAGE(program)  

#define CHECK_GL_ERROR() 

#endif

#endif //RAW_GL_GRAPHICS_H