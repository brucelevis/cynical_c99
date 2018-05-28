//
// Created by temdisponivel on 27/05/2018.
//

#ifndef RAW_GL_HOT_RELOADER_H
#define RAW_GL_HOT_RELOADER_H

#include "common.h"
#include <time.h>

#define MAX_SHADER_CACHE 32
#define MAX_TEXTURE_CACHE 128

typedef struct shader_object_cache {
    uint handle;
    
    char file_path[FILENAME_MAX];
    char both_include_file_path[FILENAME_MAX];
    char vertex_include_file_path[FILENAME_MAX];
    char fragment_include_file_path[FILENAME_MAX];
    
    time_t last_seen_modification;
} shader_object_cache_t;

typedef struct gl_object_cache {    
    uint handle;
    char file_path[FILENAME_MAX];
    time_t last_seen_modification;
} gl_object_cache_t;

typedef struct hot_realoder_data {
    shader_object_cache_t shader_caches[MAX_SHADER_CACHE];
    uint shader_caches_len;
    
    gl_object_cache_t texture_caches[MAX_TEXTURE_CACHE];
    uint texture_caches_len;
    
    char config_file_path[DEFAULT_FILE_NAME_LEN];
    bool config_file_watching;
    time_t config_file_last_seen_modification;
} hot_reloader_data;

void watch_shader_file(uint handle,
                       const char *shader_file,
                       const char *both_include_file,
                       const char *vertex_include_file,
                       const char *fragment_include_file
);

void stop_watch_shader_file(uint handle);

void watch_texture_file(uint handle, const char *file);
void stop_watch_texture_file(uint handle);

void watch_config_file(const char *file_path);
void stop_watch_config_file(const char *file_path);

void update_hot_reloader();

#endif //RAW_GL_HOT_RELOADER_H
