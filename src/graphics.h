//
// Created by Firehorse on 22/05/2018.
//

#ifndef RAW_GL_GRAPHICS_H
#define RAW_GL_GRAPHICS_H

#include "GL/glew.h"
#include "common.h"
#include "cglm/vec3.h"

typedef struct model {
    vec3 *positions;
} model_t;

typedef struct shader {
    uint handle;
} shader_t;

shader_t create_shader(const char *vertex, const char *fragment);
void destroy_shader(shader_t shader);

model_t create_quad();
void destroy_model(model_t model);

#define check_shader_compilation(shader) {\
    int compiled;\
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);\
    if (!compiled) {\
        int len;\
        CREATE_TEMP_STR_BUFFER();\
        glGetShaderInfoLog(shader, TEMP_STR_BUFFER_LEN, &len, INFO_BUFFER);\
        ERROR(INFO_BUFFER);\
    }\
}\

#define check_program_linkage(program) {\
    int compiled;\
    glGetProgramiv(program, GL_LINK_STATUS, &compiled);\
    if (!compiled) {\
        int len;\
        CREATE_TEMP_STR_BUFFER();\
        glGetProgramInfoLog(program, TEMP_STR_BUFFER_LEN, &len, INFO_BUFFER);\
        ERROR(INFO_BUFFER);\
    }\
}\

#define check_gl_error() {\
    GLenum error = glGetError();\
    if (error != GL_NO_ERROR) {\
        CREATE_TEMP_STR_BUFFER();\
        sprintf(INFO_BUFFER, "OpenGL error: '%i'\n", error);\
        ERROR(INFO_BUFFER);\
    }\
}\

#endif //RAW_GL_GRAPHICS_H