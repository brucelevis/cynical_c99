//
// Created by temdisponivel on 27/05/2018.
//

#ifndef RAW_GL_HOT_RELOADER_H
#define RAW_GL_HOT_RELOADER_H

#include "common.h"
#include <time.h>

#define MAX_SHADER_CACHE 32
#define MAX_TEXTURE_CACHE 128

typedef struct gl_object_cache {    
    uint handle;
    char file_path[FILENAME_MAX];
    time_t last_seen_modification;
} gl_object_cache_t;

typedef struct hot_realoder_data {    
    gl_object_cache_t shader_caches[MAX_SHADER_CACHE];
    uint shader_caches_len;
    
    gl_object_cache_t texture_caches[MAX_TEXTURE_CACHE];
    uint texture_caches_len;
} hot_reloader_data;

void watch_shader_file(uint handle, const char *file);
void stop_watch_shader_file(uint handle);

void watch_texture_file(uint handle, const char *file);

void update_hot_reloader();

#endif //RAW_GL_HOT_RELOADER_H
