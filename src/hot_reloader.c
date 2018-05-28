//
// Created by temdisponivel on 27/05/2018.
//

#include <mem.h>
#include <sys/stat.h>
#include "hot_reloader.h"
#include "graphics.h"

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

bool has_changed(const gl_object_cache_t *cache) {
    struct stat s;
    stat(cache->file_path, &s);
    time_t last_modified = s.st_mtime;
    double diff = difftime(last_modified, cache->last_seen_modification);
    return diff > 0;
}

void update_hot_reloader() {
    for (int i = 0; i < data.shader_caches_len; ++i) {
        gl_object_cache_t cache = data.shader_caches[i];
        if (has_changed(&cache)) {
            time(&data.shader_caches[i].last_seen_modification);
            reload_shader(cache.handle, cache.file_path);
            printf("Reloading file: '%s'!", cache.file_path);
        }
    }
}