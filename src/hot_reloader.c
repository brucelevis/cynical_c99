//
// Created by temdisponivel on 27/05/2018.
//

#include <mem.h>
#include <sys/stat.h>
#include "hot_reloader.h"
#include "graphics.h"
#include "engine.h"
#include "resources.h"

static hot_reloader_data data = {};

void watch_shader_file(uint handle, const char *file) {
    gl_object_cache_t cache;
    cache.handle = handle;
    strcpy(cache.file_path, file);

    ASSERT(data.shader_caches_len < MAX_SHADER_CACHE);
    data.shader_caches[data.shader_caches_len++] = cache;
}

void stop_watch_shader_file(uint handle) {
    for (int i = 0; i < data.shader_caches_len; ++i) {
        gl_object_cache_t shader = data.shader_caches[i];
        if (shader.handle == handle) {
            printf("remove shader watch\n");

            // TODO(temdisponivel): Create a macro for this
            for (int j = i; j < data.shader_caches_len - 1; ++j) {
                data.shader_caches[j] = data.shader_caches[j + 1];
            }
        }
    }
}

void watch_texture_file(uint handle, const char *file) {
    gl_object_cache_t cache;
    cache.handle = handle;
    strcpy(cache.file_path, file);

    ASSERT(data.texture_caches_len < MAX_TEXTURE_CACHE);
    data.texture_caches[data.texture_caches_len++] = cache;
}

void stop_watch_texture_file(uint handle) {
    for (int i = 0; i < data.texture_caches_len; ++i) {
        gl_object_cache_t shader = data.texture_caches[i];
        if (shader.handle == handle) {
            printf("remove shader watch\n");

            // TODO(temdisponivel): Create a macro for this
            for (int j = i; j < data.texture_caches_len - 1; ++j) {
                data.texture_caches[j] = data.texture_caches[j + 1];
            }
        }
    }
}

bool has_changed(const char *file_path, time_t last_modification) {
    struct stat s;
    stat(file_path, &s);
    time_t last_modified = s.st_mtime;
    double diff = difftime(last_modified, last_modification);
    return diff > 0;
}

void update_hot_reloader() {
    for (int i = 0; i < data.shader_caches_len; ++i) {
        gl_object_cache_t cache = data.shader_caches[i];
        if (has_changed(cache.file_path, cache.last_seen_modification)) {
            time(&data.shader_caches[i].last_seen_modification);
            reload_shader(cache.handle, cache.file_path);
        }
    }

    for (int i = 0; i < data.texture_caches_len; ++i) {
        gl_object_cache_t cache = data.texture_caches[i];
        if (has_changed(cache.file_path, cache.last_seen_modification)) {
            time(&data.texture_caches[i].last_seen_modification);
            image_t img;
            bool loaded = load_image_from_file(cache.file_path, &img);
            ASSERT(!loaded);
            update_texture_data(cache.handle, &img);
        }
    }
    
    if (data.config_file_watching) {
        if (has_changed(data.config_file_path, data.config_file_last_seen_modification)) {
            time(&data.config_file_last_seen_modification);
            update_config(data.config_file_path, &engine_config);
        }
    }
}

void watch_config_file(const char *file_path) {
    strcpy(data.config_file_path, file_path);
    data.config_file_watching = true;
}

void stop_watch_config_file(const char *file_path) {
    memset(data.config_file_path, 0, sizeof(data.config_file_path));
    data.config_file_watching = false;
}