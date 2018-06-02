//
// Created by temdisponivel on 01/06/2018.
//

#ifndef RAW_GL_RESOURCE_MANAGER_H
#define RAW_GL_RESOURCE_MANAGER_H

#include "common.h"
#include "graphics.h"

#define MAX_TEXTURES 64

typedef struct texture_resource {
    int id;
    texture_t *texture;
    int reference_count;
} texture_resource_t;

typedef struct resources {
    texture_resource_t textures[MAX_TEXTURES];
    uint textures_len;
} resources_t;

// TODO(temdisponivel): Move this macro to a more accessible file


void print_resources();

void free_unused_resources();

texture_t *get_texture_resource(const char *texture_path);
void free_texture_resource(texture_t *texture);

#endif //RAW_GL_RESOURCE_MANAGER_H
