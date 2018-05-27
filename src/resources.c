//
// Created by temdisponivel on 27/05/2018.
//

#include "resources.h"
#include "string_helper.h"

bool read_shader_file(const char *file_path, char *vertex_buffer, char *fragment_buffer) {
    FILE *file = fopen(file_path, "rb");

    if (!file) {
        return false;
    }

    CREATE_TEMP_STR_BUFFER();

    while (!feof(file)) {
        fscanf(file, "%s", TEMP_BUFFER);

        if (strcmp(TEMP_BUFFER, "#start_vertex") == 0) {
            fseek(file, 0, SEEK_CUR);
            int file_start = ftell(file);
            int file_end;
            
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
            int file_end;

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

#if DEV && 0
    printf("Vertex shader: \n '%s' \n", vertex_buffer);
    printf("Fragment shader: \n '%s' \n", fragment_buffer);
#endif

    return true;
}

bool read_material_definition_file(const char *file_path, material_definition_t *definition) {
    FILE *file = fopen(file_path, "rb");

    if (!file) {
        return false;
    }

    char header_buffer[128];
    int current_uniform_count;

    char uniform_name_buffer[DEFAULT_IDENTIFIER_NAME_LEN];
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