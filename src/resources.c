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

    char header_buffer[128];
    int current_uniform_count;

    char uniform_name_buffer[DEFAULT_NAME_LEN];
    char uniform_value_buffer[512];

    const int seek_shader_files = 0;
    const int seek_header = 1;
    const int read_textures = 2;
    const int read_floats = 3;
    const int read_mat4 = 4;
    int state = seek_shader_files;

    while (!feof(file)) {
        if (state == seek_shader_files) {
            fscanf(file, "%s\n", definition->shader_file);
            state = seek_header;
        } else if (state == seek_header) {
            // Prevent from reading the header again when it did not reach end of file
            header_buffer[0] = '\0';

            fscanf(file, "%s %i", header_buffer, &current_uniform_count);
            if (strcmp(header_buffer, "textures") == 0) {
                state = read_textures;
            } else if (strcmp(header_buffer, "floats") == 0) {
                state = read_floats;
            } else if (strcmp(header_buffer, "mat4s") == 0) {
                state = read_mat4;
            }
        } else if (state == read_textures) {

            definition->textures_len = (uint) current_uniform_count;
            for (int i = 0; i < current_uniform_count; ++i) {
                fscanf(file, "%s %s", uniform_name_buffer, uniform_value_buffer);
                
                strcpy(definition->textures[i].uniform_name, uniform_name_buffer);
                strcpy(definition->textures[i].image_file_name, uniform_value_buffer);
            }

            state = seek_header;

        } else if (state == read_floats) {

            definition->floats_len = (uint) current_uniform_count;
            
            for (int i = 0; i < current_uniform_count; ++i) {
                float default_value;
                fscanf(file, "%s %f", uniform_name_buffer, &default_value);
                
                
                strcpy(definition->floats[i].uniform_name, uniform_name_buffer);
                definition->floats[i].default_value = default_value;
            }

            state = seek_header;

        } else if (state == read_mat4) {
            
            definition->mat4s_len = (uint) current_uniform_count;
            for (int i = 0; i < current_uniform_count; ++i) {
                mat4_t default_value;
                fscanf(
                        file,
                        "%s %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f",
                        uniform_name_buffer,
                        &default_value.x.x,
                        &default_value.x.y,
                        &default_value.x.z,
                        &default_value.x.w,
                        &default_value.y.x,
                        &default_value.y.y,
                        &default_value.y.z,
                        &default_value.y.w,
                        &default_value.z.x,
                        &default_value.z.y,
                        &default_value.z.z,
                        &default_value.z.w,
                        &default_value.w.x,
                        &default_value.w.y,
                        &default_value.w.z,
                        &default_value.w.w
                );

                strcpy(definition->mat4s[i].uniform_name, uniform_name_buffer);
                definition->mat4s[i].default_value = default_value;
            }

            state = seek_header;
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