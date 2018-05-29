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

void watch_shader_file(uint handle, 
                       const char *shader_file,
                       const char *both_include_file,
                       const char *vertex_include_file,
                       const char *fragment_include_file
) {
    shader_object_cache_t cache;
    
    cache.handle = handle;
    strcpy(cache.file_path, shader_file);
    strcpy(cache.both_include_file_path, both_include_file);
    strcpy(cache.vertex_include_file_path, vertex_include_file);
    strcpy(cache.fragment_include_file_path, fragment_include_file);
    
    time(&cache.last_seen_modification);

    ASSERT(data.shader_caches_len < MAX_SHADER_CACHE);
    data.shader_caches[data.shader_caches_len++] = cache;
}

void stop_watch_shader_file(uint handle) {
    bool found = false;
    for (int i = 0; i < data.shader_caches_len; ++i) {
        shader_object_cache_t shader = data.shader_caches[i];
        if (shader.handle == handle) {
            // TODO(temdisponivel): Create a macro for this
            for (int j = i; j < data.shader_caches_len - 1; ++j) {
                data.shader_caches[j] = data.shader_caches[j + 1];
            }

            found = true;
            data.shader_caches_len--;
        }
    }
    
    ASSERT(found);
}

void watch_texture_file(uint handle, const char *file) {
    gl_object_cache_t cache;
    cache.handle = handle;
    strcpy(cache.file_path, file);

    time(&cache.last_seen_modification);

    ASSERT(data.texture_caches_len < MAX_TEXTURE_CACHE);
    data.texture_caches[data.texture_caches_len++] = cache;
}

void stop_watch_texture_file(uint handle) {
    bool found = false;
    for (int i = 0; i < data.texture_caches_len; ++i) {
        gl_object_cache_t shader = data.texture_caches[i];
        if (shader.handle == handle) {
            
            // TODO(temdisponivel): Create a macro for this
            for (int j = i; j < data.texture_caches_len - 1; ++j) {
                data.texture_caches[j] = data.texture_caches[j + 1];
            }

            found = true;
            data.texture_caches_len--;
        }
    }
    
    ASSERT(found);
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
        shader_object_cache_t cache = data.shader_caches[i];
        
        bool something_changed = false;
        something_changed |= has_changed(cache.file_path, cache.last_seen_modification);
        
        something_changed |= has_changed(cache.both_include_file_path, cache.last_seen_modification);
        
        something_changed |= has_changed(cache.vertex_include_file_path, cache.last_seen_modification);
        
        something_changed |= has_changed(cache.fragment_include_file_path, cache.last_seen_modification);

        if (something_changed) {
            time(&data.shader_caches[i].last_seen_modification);
            reload_shader_sources(cache.handle, cache.file_path);
            
            // Only update only at a time
            break;
        }
    }

    for (int i = 0; i < data.texture_caches_len; ++i) {
        gl_object_cache_t cache = data.texture_caches[i];
        if (has_changed(cache.file_path, cache.last_seen_modification)) {
            time(&data.texture_caches[i].last_seen_modification);
            
            reload_texture(cache.handle, cache.file_path);

            // Only update only at a time
            break;
        }
    }

    for (int i = 0; i < data.material_definition_caches_len; ++i) {
        material_definition_cache_t cache = data.material_definition_caches[i];
        if (has_changed(cache.file_path, cache.last_seen_modification)) {
            time(&data.material_definition_caches[i].last_seen_modification);

            reload_material(cache.file_path,  (material_t *) cache.material);
            
            // Only update only at a time
            break;
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
    time(&data.config_file_last_seen_modification);
}

void stop_watch_config_file(const char *file_path) {
    memset(data.config_file_path, 0, sizeof(data.config_file_path));
    data.config_file_watching = false;
}

void watch_material_definition_file(const material_t *material, const char *file_path) {
    material_definition_cache_t cache;
    strcpy(cache.file_path, file_path);
    time(&cache.last_seen_modification);
    cache.material = material;
    
    
    ASSERT(data.material_definition_caches_len < MAX_MATERIAL_DEFINITION_CACHE);
    
    data.material_definition_caches[data.material_definition_caches_len++] = cache;
}

void stop_watch_material_definition_file(const material_t *material) {
    bool found = false;
    for (int i = 0; i < data.material_definition_caches_len; ++i) {
        material_definition_cache_t cache = data.material_definition_caches[i];
        if (cache.material == material) {

            // TODO(temdisponivel): Create a macro for this
            for (int j = i; j < data.material_definition_caches_len - 1; ++j) {
                data.material_definition_caches[j] = data.material_definition_caches[j + 1];
            }

            found = true;
            data.material_definition_caches_len--;
        }
    }

    ASSERT(found);
}