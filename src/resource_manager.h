//
// Created by temdisponivel on 01/06/2018.
//

#ifndef RAW_GL_RESOURCE_MANAGER_H
#define RAW_GL_RESOURCE_MANAGER_H

#include "common.h"
#include "graphics.h"

#define MAX_TEXTURES_RESOURCES 64
#define MAX_IMAGES_RESOURCES MAX_TEXTURES_RESOURCES
#define MAX_SHADERS_RESOURCES 16
#define MAX_MATERIALS_RESOURCES 16

typedef struct texture_resource {
    int id;
    texture_t *texture;
    int reference_count;
} texture_resource_t;

typedef struct shader_resource {
    int id;
    shader_t *shader;
    int reference_count;
} shader_resource_t;

typedef struct material_resource {
    int id;
    material_t *material;
    int reference_count;
} material_resource_t;

typedef struct image_resource {
    int id;
    image_t *image;
    int reference_count;
} image_resource_t;

typedef struct resources {
    texture_resource_t textures[MAX_TEXTURES_RESOURCES];
    uint textures_len;
    
    shader_resource_t shaders[MAX_SHADERS_RESOURCES];
    uint shaders_len;

    material_resource_t materials[MAX_MATERIALS_RESOURCES];
    uint materials_len;
    
    image_resource_t images[MAX_IMAGES_RESOURCES];
    uint images_len;
} resources_t;

// TODO(temdisponivel): Move this macro to a more accessible file


void print_resources();

void free_unused_resources();

texture_t *get_texture_resource(const char *texture_path);
void free_texture_resource(const texture_t *texture);

shader_t *get_shader_resource(const char *shader_path);
void free_shader_resource(const shader_t *shader);

material_t *get_material_resource(const char *material_path);
void free_material_resource(const material_t *material);

image_t *get_image_resource(const char *image_path);
void free_image_resource(const image_t *image);

#endif //RAW_GL_RESOURCE_MANAGER_H
