//
// Created by temdisponivel on 11/06/2018.
//

#ifndef RAW_GL_TEXT_H
#define RAW_GL_TEXT_H

#include "graphics.h"

#define INITIAL_CHARACTER 0
#define MAX_CHARACTERS 128

typedef struct code_point {
    texture_t texture;
    vec2_t offset;
} code_point_t;

typedef struct font {
    code_point_t code_points[MAX_CHARACTERS];
    material_t *material; // TODO(temdisponivel): Maybe this should be global or passed into the draw functions as a parameter
} font_t;

void load_font(const char *font_path, float size, material_t *material, font_t *dest);

void draw_string(const font_t *font, const char *string, vec2_t position);

#endif //RAW_GL_TEXT_H
