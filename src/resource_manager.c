//
// Created by temdisponivel on 01/06/2018.
//

#include <malloc.h>
#include "resource_manager.h"
#include "string_helper.h"

static resources_t resources = {};

void print_resources() {
    printf("Textures count: %i\n", resources.textures_len);
    fflush(stdout);
}

void free_unused_resources() {
    for (int i = resources.textures_len - 1; i >= 0; --i) {
        texture_resource_t resource = resources.textures[i];
        
        if (resource.reference_count <= 0) {
            destroy_texture(resource.texture);
            resources.textures[i].texture = null;

            array_move_to_left(resources.textures, &resources.textures_len, i);
        }
    }
}

texture_t *get_texture_resource(const char *texture_path) {
    texture_t *texture = null;
    
    int hash = hash_string(texture_path);
    for (int i = 0; i < resources.textures_len; ++i) {
        texture_resource_t resource = resources.textures[i];
        if (resource.id == hash) {
            resources.textures[i].reference_count++;
            texture = resource.texture;
        }
    }
    
    if (texture == null) {
        texture_resource_t resource;

        resource.texture = (texture_t *) malloc(sizeof(texture_t));
        create_texture_from_file(texture_path, resource.texture);
        resource.id = hash;
        resource.reference_count = 1;
        
        array_add(resources.textures, MAX_TEXTURES, &resources.textures_len, resource);
        resources.textures[resources.textures_len++] = resource;
        
        texture = resource.texture;
    }
    
    return texture;
}

void free_texture_resource(texture_t *texture) {
    for (int i = 0; i < resources.textures_len; ++i) {
        texture_resource_t resource = resources.textures[i];
        if (resource.texture == texture) {
            if (resource.reference_count > 0) {
                resources.textures[i].reference_count--;
            }           
        }
    }
}