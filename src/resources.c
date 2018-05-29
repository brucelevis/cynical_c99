//
// Created by temdisponivel on 27/05/2018.
//

#include "resources.h"
#include "file.h"



bool read_shader_file(
        const char *file_path,
        char *vertex_buffer,
        char *fragment_buffer

#if DEV
        , 
        char *both_include_file_path,
        char *vert_include_file_path,
        char *frag_include_file_path
#endif
) {
    
    char *start_vertex_buffer = vertex_buffer;
    char *start_frag_buffer = fragment_buffer;
    
    FILE *file = fopen(file_path, "rb");

    if (!file) {
        return false;
    }
    
    CREATE_TEMP_STR_BUFFER();

    while (!feof(file)) {
        fscanf(file, "%s", TEMP_BUFFER);

        if (strcmp(TEMP_BUFFER, "#include") == 0) {
            char include_file_path[DEFAULT_FILE_NAME_LEN];
            char include_file_type[DEFAULT_NAME_LEN];
            fscanf(file, "%s %s", include_file_type, include_file_path);
            
            CREATE_TEMP_NAMED_STR_BUFFER(include_buffer);
            CLEAR_TEMP_NAMED_STR_BUFFER(include_buffer);
            
            if (strlen(include_file_path) > 0) {
                uint file_len;
                bool read = read_file_string(
                        include_file_path,
                        include_buffer,
                        TEMP_STR_BUFFER_LEN,
                        &file_len
                );

                ASSERT(read);

                uint include_buffer_len = strlen(include_buffer);
                
                bool vertex = false;
                bool fragment = false;
                if (strcmp(include_file_type, "both") == 0) {
                    strcpy(both_include_file_path, include_file_path);
                    vertex = true;
                    fragment = true;
                } else if (strcmp(include_file_type, "vertex") == 0) {
                    strcpy(vert_include_file_path, include_file_path);
                    vertex = true;
                } else if (strcmp(include_file_type, "fragment") == 0) {
                    strcpy(frag_include_file_path, include_file_path);
                    fragment = true;
                } else {
                    ASSERT(false);
                }
                
                if (vertex) {
                    strcpy(vertex_buffer, include_buffer);
                    vertex_buffer += include_buffer_len;
                }
                
                if (fragment) {
                    strcpy(fragment_buffer, include_buffer);
                    fragment_buffer += include_buffer_len;
                }
            }
        } else if (strcmp(TEMP_BUFFER, "#start_vertex") == 0) {
            fseek(file, 0, SEEK_CUR);
            int file_start = ftell(file);
            int file_end = file_start;
            
            while (true) {
                fscanf(file, "%s", TEMP_BUFFER);
                fseek(file, 0, SEEK_CUR);
                int current = ftell(file);
                if (strcmp(TEMP_BUFFER, "#end_vertex") == 0) {
                    break;
                } else {
                    file_end = current;
                }
            }
            
            fseek(file, file_start, SEEK_SET);
            fread(vertex_buffer, sizeof(char), (uint) file_end - file_start, file);

        } else if (strcmp(TEMP_BUFFER, "#start_fragment") == 0) {
            fseek(file, 0, SEEK_CUR);
            int file_start = ftell(file);
            int file_end = file_start;

            while (true) {
                fscanf(file, "%s", TEMP_BUFFER);
                fseek(file, 0, SEEK_CUR);
                int current = ftell(file);
                if (strcmp(TEMP_BUFFER, "#end_fragment") == 0) {
                    break;
                } else {
                    file_end = current;
                }
            }

            fseek(file, file_start, SEEK_SET);
            fread(fragment_buffer, sizeof(char), (uint) file_end - file_start, file);

        }
    }

#if DEV
    printf("Vertex shader: \n '%s' \n", start_vertex_buffer);
    printf("Fragment shader: \n '%s' \n", start_frag_buffer);
#endif

    fclose(file);
    return true;
}

bool read_material_definition_file(const char *file_path, material_definition_t *definition) {
    FILE *file = fopen(file_path, "rb");

    if (!file) {
        return false;
    }
    
    char helper_buffer[128];
    
    while (!feof(file)) {
        fscanf(file, "%s", helper_buffer);
        if (strcmp(helper_buffer, "shader") == 0) {
           fscanf(file, "%s", definition->shader_file);
        } else if (strcmp(helper_buffer, "texture") == 0) {
            char name_buffer[128];
            fscanf(file, "%s %s", name_buffer, helper_buffer);
            
            ASSERT(strlen(name_buffer));
            ASSERT(strlen(helper_buffer));
            
            texture_uniform_definition_t def;
            strcpy(def.uniform_name, name_buffer);
            strcpy(def.image_file_name, helper_buffer);
            
            ASSERT(definition->textures_len < MAX_TEXTURES);
            
            definition->textures[definition->textures_len++] = def;            
        } else if (strcmp(helper_buffer, "float") == 0) {
            
            float value;
            fscanf(file, "%s %f", helper_buffer, &value);

            ASSERT(strlen(helper_buffer));

            float_uniform_definition_t def;
            strcpy(def.uniform_name, helper_buffer);
            def.default_value = value;

            ASSERT(definition->floats_len < MAX_FLOATS);

            definition->floats[definition->floats_len++] = def;
        } else if (strcmp(helper_buffer, "mat4") == 0) {

            mat4_t value;
            fscanf(
                    file,
                    "%s %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f",
                    helper_buffer,
                    &value.x.x,
                    &value.x.y,
                    &value.x.z,
                    &value.x.w,
                    &value.y.x,
                    &value.y.y,
                    &value.y.z,
                    &value.y.w,
                    &value.z.x,
                    &value.z.y,
                    &value.z.z,
                    &value.z.w,
                    &value.w.x,
                    &value.w.y,
                    &value.w.z,
                    &value.w.w
            );

            ASSERT(strlen(helper_buffer));

            mat4_uniform_definition_t def;
            strcpy(def.uniform_name, helper_buffer);
            def.default_value = value;

            ASSERT(definition->mat4s_len < MAX_MAT4S);
            
            definition->mat4s[definition->mat4s_len++] = def;
        }
    }

    fclose(file);
    
    return true;
}

bool read_config_file(const char *file_path, config_t *config) {
    return update_config(file_path, config);
}

bool update_config(const char *file_path, config_t *config) {
    FILE *file = fopen(file_path, "rb");

    if (!file) {
        return false;
    }

    char header_buffer[128];

    const int seek_config_type = 0;
    const int read_resolution = 1;
    const int read_window_title = 2;
    int state = seek_config_type;

    while (!feof(file)) {
        if (state == seek_config_type) {
            fscanf(file, "%s", header_buffer);
            if (strcmp(header_buffer, "#resolution") == 0) {
                state = read_resolution;
            } else if (strcmp(header_buffer, "#window-title") == 0) {
                state = read_window_title;
            }
        } else {
            if (state == read_resolution) {
                fscanf(file, "%f %f", &config->resolution.x, &config->resolution.y);
                state = seek_config_type;
            } else if (state == read_window_title) {
                fscanf(file, "%s", config->window_title);
                state = seek_config_type;
            }
        }
    }

    config->dirty = true;

    fclose(file);
}