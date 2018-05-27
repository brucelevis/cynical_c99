//
// Created by temdisponivel on 27/05/2018.
//

#ifndef RAW_GL_RESOURCE_H
#define RAW_GL_RESOURCE_H

#include "graphics.h"
#include "common.h"

typedef enum resource_type {
    VERTEX_SHADER,
    FRAGMENT_SHADER,
    IMAGE,
} resource_type_t; 

typedef struct resources {
    
} resource_t;

bool read_shader_file(const char *file_path, char *vertex_buffer, char *fragment_buffer);

bool read_material_definition_file(const char *file_path, _OUT_ material_definition_t *definition);

#endif //RAW_GL_RESOURCE_H
