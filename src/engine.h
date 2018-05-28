//
// Created by temdisponivel on 27/05/2018.
//

#ifndef RAW_GL_ENGINE_H
#define RAW_GL_ENGINE_H

#include "math/maths.h"

typedef struct config {
    vec2_t resolution;
    char window_title[DEFAULT_NAME_LEN];
    bool dirty;
} config_t;

extern config_t engine_config;

#endif //RAW_GL_ENGINE_H
