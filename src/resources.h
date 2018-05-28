//
// Created by temdisponivel on 27/05/2018.
//

#ifndef RAW_GL_RESOURCE_H
#define RAW_GL_RESOURCE_H

#include "graphics.h"
#include "common.h"
#include "engine.h"

bool read_shader_file(
        const char *file_path, 
        char *vertex_buffer, 
        char *fragment_buffer
#if DEV
        ,
        char *both_include_file_path,
        char *vert_include_file_path,
        char *frag_include_file_path
#endif
);

bool read_material_definition_file(const char *file_path, material_definition_t *definition);

bool read_config_file(const char *file_path, config_t *config);

bool update_config(const char *file_path, config_t *config);

#endif //RAW_GL_RESOURCE_H
