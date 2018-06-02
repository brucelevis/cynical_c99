//
// Created by temdisponivel on 01/06/2018.
//

#include <malloc.h>
#include <mem.h>
#include "resource_manager.h"
#include "string_helper.h"
#include "hot_reloader.h"
#include "resources.h"
#include "stb_image.h"
#include "file.h"

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
            free(resources.textures[i].texture);
            resources.textures[i].texture = null;

            array_move_to_left(resources.textures, &resources.textures_len, i);
        }
    }

    for (int i = resources.shaders_len - 1; i >= 0; --i) {
        shader_resource_t resource = resources.shaders[i];

        if (resource.reference_count <= 0) {
            destroy_shader(resource.shader);
            free(resources.shaders[i].shader);
            resources.shaders[i].shader = null;

            array_move_to_left(resources.shaders, &resources.shaders_len, i);
        }
    }

    for (int i = resources.materials_len - 1; i >= 0; --i) {
        material_resource_t resource = resources.materials[i];

        if (resource.reference_count <= 0) {
            destroy_material(resource.material);
            free(resources.materials[i].material);
            resources.materials[i].material = null;

            array_move_to_left(resources.materials, &resources.materials_len, i);
        }
    }

    for (int i = resources.images_len - 1; i >= 0; --i) {
        image_resource_t resource = resources.images[i];

        if (resource.reference_count <= 0) {
            destroy_image(resource.image);
            free(resources.images[i].image);
            resources.images[i].image = null;

            array_move_to_left(resources.images, &resources.images_len, i);
        }
    }
}


void create_texture_from_file(const char *file_path, texture_t *dest) {
    image_t *img = get_image_resource(file_path);
    create_texture(img, dest);
    free_image_resource(img);
}

texture_t *get_texture_resource(const char *texture_path) {
    texture_t *texture = null;
    
    int hash = hash_string(texture_path);
    for (int i = 0; i < resources.textures_len; ++i) {
        texture_resource_t resource = resources.textures[i];
        if (resource.id == hash) {
            resources.textures[i].reference_count++;
            texture = resource.texture;
            break;
        }
    }
    
    if (texture == null) {
        // TODO(temdisponivel): Remove this after our temp memory/custom allocator
        texture = (texture_t *) malloc(sizeof(texture_t));
        create_texture_from_file(texture_path, texture);

        texture_resource_t resource;
        resource.texture = texture;
        resource.id = hash;
        resource.reference_count = 1;
        
        array_add(resources.textures, MAX_TEXTURES_RESOURCES, &resources.textures_len, resource);
    }
    
    return texture;
}

void free_texture_resource(const texture_t *texture) {
    for (int i = 0; i < resources.textures_len; ++i) {
        texture_resource_t resource = resources.textures[i];
        if (resource.texture == texture) {
            if (resource.reference_count > 0) {
                resources.textures[i].reference_count--;
            }           
        }
    }
}

void create_shader_from_file(const char *shader_file, shader_t *shader) {

    uint program = glCreateProgram();

#if DEV

    char both_include_file_path[DEFAULT_FILE_NAME_LEN];
    memset(both_include_file_path, 0, DEFAULT_FILE_NAME_LEN * sizeof(char));

    char vert_include_file_path[DEFAULT_FILE_NAME_LEN];
    memset(vert_include_file_path, 0, DEFAULT_FILE_NAME_LEN * sizeof(char));

    char frag_include_file_path[DEFAULT_FILE_NAME_LEN];
    memset(frag_include_file_path, 0, DEFAULT_FILE_NAME_LEN * sizeof(char));

#endif


    reload_shader_sources(
            program,
            shader_file,
            both_include_file_path,
            vert_include_file_path,
            frag_include_file_path
    );

    watch_shader_file(
            program,
            shader_file,
            both_include_file_path,
            vert_include_file_path,
            frag_include_file_path
    );

    shader->handle = program;
}

shader_t *get_shader_resource(const char *shader_path) {
    shader_t *shader = null;
    
    int hash = hash_string(shader_path);
    for (int i = 0; i < resources.shaders_len; ++i) {
        shader_resource_t resource = resources.shaders[i];
        if (resource.id == hash) {
            shader = resource.shader;
            resources.shaders[i].reference_count++;
            break;
        }
    }
    
    if (shader == null) {
        shader = (shader_t *) malloc(sizeof(shader_t));
        create_shader_from_file(shader_path, shader);
        
        shader_resource_t resource;
        resource.shader = shader;
        resource.id = hash;
        resource.reference_count = 1;
        
        array_add(resources.shaders, MAX_SHADERS_RESOURCES, &resources.shaders_len, resource);
    }
    
    return shader;
}

void free_shader_resource(const shader_t *shader) {
    for (int i = 0; i < resources.shaders_len; ++i) {
        shader_resource_t resource = resources.shaders[i];
        if (resource.shader == shader) {
            if (resource.reference_count > 0) {
                resources.shaders[i].reference_count--;
            }
        }
    }
}


void create_material_from_file(const char *file_path, material_t *dest) {
    material_definition_t definition;
    bool read = read_material_definition_file(file_path, &definition);
    ASSERT(read);
    create_material(&definition, dest);

    watch_material_definition_file(dest, file_path);
}


material_t *get_material_resource(const char *material_path) {
    material_t *material = null;

    int hash = hash_string(material_path);
    for (int i = 0; i < resources.materials_len; ++i) {
        material_resource_t resource = resources.materials[i];
        if (resource.id == hash) {
            material = resource.material;
            resources.materials[i].reference_count++;
            break;
        }
    }

    if (material == null) {
        material = (material_t *) malloc(sizeof(material_t));
        create_material_from_file(material_path, material);

        material_resource_t resource;
        resource.material = material;
        resource.id = hash;
        resource.reference_count = 1;

        array_add(resources.materials, MAX_MATERIALS_RESOURCES, &resources.materials_len, resource);
    }

    return material;
}

void free_material_resource(const material_t *material) {
    for (int i = 0; i < resources.materials_len; ++i) {
        material_resource_t resource = resources.materials[i];
        if (resource.material == material) {
            if (resource.reference_count > 0) {
                resources.materials[i].reference_count--;
            }
        }
    }
}

bool create_image_from_file(const char *image_path, image_t *dest) {

    // TODO(temdisponivel): Create a buffer in order to prevent allocations
    uint len;
    byte *file_data = read_file_data_alloc(image_path, &len);

#if DEV
    if (!file_data) {
        file_data = read_file_data_alloc(DEFAULT_IMAGE_FILE_PATH, &len);
        ASSERT(false);
    }
#endif

    if (!file_data) {
        return false;
    }

    int width, height, channels;

    stbi_set_flip_vertically_on_load(true);
    byte *image_data = stbi_load_from_memory(file_data, len, &width, &height, &channels, 4);
    free_file_data(file_data);

    if (image_data == null) {
        return false;
    }

    strcpy(dest->file_path, image_path);
    dest->data = image_data;
    dest->size = vec2_make(width, height);
}

void destroy_image(const image_t *image) {
    stbi_image_free(image->data);
}

image_t *get_image_resource(const char *image_path) {
    image_t *image = null;

    int hash = hash_string(image_path);
    for (int i = 0; i < resources.images_len; ++i) {
        image_resource_t resource = resources.images[i];
        if (resource.id == hash) {
            image = resource.image;
            resources.images[i].reference_count++;
            break;
        }
    }

    if (image == null) {
        image = (image_t *) malloc(sizeof(image_t));
        create_image_from_file(image_path, image);

        image_resource_t resource;
        resource.image = image;
        resource.id = hash;
        resource.reference_count = 1;

        array_add(resources.images, MAX_IMAGES_RESOURCES, &resources.images_len, resource);
    }

    return image;
}

void free_image_resource(const image_t *image) {
    for (int i = 0; i < resources.images_len; ++i) {
        image_resource_t resource = resources.images[i];
        if (resource.image == image) {
            if (resource.reference_count > 0) {
                resources.images[i].reference_count--;
            }
        }
    }
}