/*
 * TODO: FIX DESTIONATION VECTORS - PASS THEM AS POINTERS
 */

#include <stdio.h>
#include <malloc.h>
#include "GL/glew.h"
#include "GL/GL.h"
#include "GLFW/glfw3.h"
#include "common.h"
#include "file.h"
#include "graphics.h"
#include "math/maths.h"
#include "math/test.h"
#include "string_helper.h"

#define FILE_BUFFER_SIZE 2048
byte FILE_BUFFER[FILE_BUFFER_SIZE];

material_definition_t parse_material_def(const char *file_path);
void parse_full_shader(const char *file_name);

int main() {
    
    parse_full_shader("data/shaders/full_shader.glsl");
    return 1;
        
    glfwInit();

    GLFWwindow *window = glfwCreateWindow(1024, 768, "Hello world!", NULL, NULL);
    
    if (!window) {
        return -1;
    }

    glfwMakeContextCurrent(window);

    glewInit();

    char *vert_shader = FILE_BUFFER;
    uint len;
    file_status_t result = read_file_string(
            "data/shaders/default_vert.glsl",
            vert_shader,
            FILE_BUFFER_SIZE,
            &len
    );

    if (result != FILE_OK) {
        ERROR("File not found!\n");
        return -1;
    }

    char *frag_shader = FILE_BUFFER + len;
    result = read_file_string(
            "data/shaders/default_frag.glsl",
            frag_shader,
            FILE_BUFFER_SIZE,
            &len
    );

    if (result != FILE_OK) {
        ERROR("File not found!\n");
        return -1;
    }

    shader_t shader = create_shader(vert_shader, frag_shader);
    model_t quad = create_quad();
    mesh_t quad_mesh = create_mesh(quad);
    
    mat4_t MVP, view, proj, view_proj, model;
    vec3_t dir, pos, up;
    
    mat4_identity(&MVP);
    mat4_identity(&view);
    mat4_identity(&proj);
    mat4_identity(&model);
    
    quat_t rot;
    vec3_t axis = VEC3_MAKE_UP();
    quat_angle_axis(&axis, RAD(0), &rot);
    
    transform_t trans = trans_make(vec3_make(0, 0, -10), vec3_make(1, 1, 1), rot);
    trans_get_mat4(&trans, &model);
    
    vec3_set(0, 0, -1, &dir);
    vec3_set(0, 0, 1, &pos);
    vec3_set(0, 1, 0, &up);
    
    mat4_look(&pos, &dir, &up, &view);
    mat4_perspective(RAD(45), 16 / 9.f, .01f, 10000.f, &proj);

    mat4_mul(&proj, &view, &view_proj);
    mat4_mul(&view_proj, &model, &MVP);
    
    glUseProgram(shader.handle);
    int loc = glGetUniformLocation(shader.handle, "MVP");
    glUniformMatrix4fv(loc, 1, GL_FALSE, &MVP);
    CHECK_GL_ERROR();
    
    image_t img;
    if (!load_image("data/textures/witness.jpg", &img)) {
        return -100;
    }

    texture_t tex = create_texture(&img);

    int main_texture_loc = glGetUniformLocation(shader.handle, "main_texture");
    int bump_map_loc = glGetUniformLocation(shader.handle, "bump_map_texture");
    /*
    texture_uniform_definition_t tex_definitions[2];
    tex_definitions[0].image_file_name = "data/textures/witness.jpg";
    tex_definitions[0].uniform_name = "main_texture";

    tex_definitions[1].image_file_name = "data/textures/default.png";
    tex_definitions[1].uniform_name = "bump_map_texture";
    
    float_uniform_definition_t float_uniforms[1];
    float_uniforms[0].uniform_name = "float_value";
    float_uniforms[0].default_value = 5;

    mat4_uniform_definition_t mat4_uniforms[1];
    mat4_uniforms[0].uniform_name = "MVP";
    mat4_uniforms[0].default_value = MVP;
    
    material_definition_t definition;
    definition.vertex_shader_file = "data/shaders/default_vert.glsl";
    definition.fragment_shader_file = "data/shaders/default_frag.glsl";
    
    definition.textures_len = 2;
    definition.textures = (texture_uniform_definition_t*) tex_definitions;
    
    definition.floats_len = 1;
    definition.floats = (float_uniform_definition_t *) float_uniforms;

    definition.mat4s_len = 1;
    definition.mat4s = (mat4_uniform_definition_t *) mat4_uniforms;
    */

    material_definition_t definition = parse_material_def("data/shaders/default_material.mat_def");
    material_t material = create_material(&definition);
    
    material.mat4_uniforms[0].value = MVP;
    
    CHECK_GL_ERROR();
    
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        int width, height;
        glfwGetWindowSize(window, &width, &height);
        glViewport(0, 0, width, height);

        glClearColor(0, 0, 0, 255);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        use_material(&material);
        
        //assert(shader.handle);
        draw_mesh(quad_mesh);
        
        //glBindTexture(GL_TEXTURE_2D, 0);
        
        glfwSwapBuffers(window);
    }

    destroy_shader(shader);
    destroy_model(quad);
    destroy_mesh(quad_mesh);
    destroy_image(&img);
    destroy_texture(&tex);
    destroy_material(&material);

    CHECK_GL_ERROR();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

material_definition_t parse_material_def(const char *file_path) {
    FILE *file = fopen(file_path, "rb");
    
    if (!file) {
        material_definition_t m;
        return m;
    }
    
    char vertex_file_buffer[128];
    char fragment_file_buffer[128];
    
    char header_buffer[128];
    int current_uniform_count;
    
    char uniform_name_buffer[64];
    char uniform_value_buffer[512];
    
    texture_uniform_definition_t *textures = null;
    int textures_len = 0;
    
    float_uniform_definition_t *floats = null;
    int floats_len = 0;

    mat4_uniform_definition_t *mat4s = null;
    int mat4s_len = 0;
        
    const int seek_shader_files = 0;
    const int seek_header = 1;
    const int read_textures = 2;
    const int read_floats = 3;
    const int read_mat4 = 4;
    int state = seek_shader_files;
    
    while (!feof(file)) {
        if (state == seek_shader_files) {
            fscanf(file, "%s %s\n", vertex_file_buffer, fragment_file_buffer);
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
            
            textures_len = current_uniform_count;
            textures = malloc(sizeof(texture_uniform_definition_t) * textures_len);
            for (int i = 0; i < textures_len; ++i) {
                fscanf(file, "%s %s", uniform_name_buffer, uniform_value_buffer);
                textures[i].uniform_name = string_copy(uniform_name_buffer);
                textures[i].image_file_name = string_copy(uniform_value_buffer);
            }
            
            state = seek_header;
            
        } else if (state == read_floats) {
            
            floats_len = current_uniform_count;
            floats = malloc(sizeof(float_uniform_definition_t) * floats_len);
            for (int i = 0; i < floats_len; ++i) {
                float default_value;
                fscanf(file, "%s %f", uniform_name_buffer, &default_value);
                floats[i].uniform_name = string_copy(uniform_name_buffer);
                floats[i].default_value = default_value;
            }
            
            state = seek_header;
            
        } else if (state == read_mat4) {
            
            mat4s_len = current_uniform_count;
            mat4s = malloc(sizeof(mat4_uniform_definition_t) * mat4s_len);
            for (int i = 0; i < mat4s_len; ++i) {
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
                
                mat4s[i].uniform_name = string_copy(uniform_name_buffer);
                mat4s[i].default_value = default_value;
            }
            
            state = seek_header;
        }
    }
    
    material_definition_t definition;
    definition.floats_len = (uint) floats_len;
    definition.floats = floats;
    
    definition.mat4s_len = (uint) mat4s_len;
    definition.mat4s = mat4s;

    definition.textures_len = (uint) textures_len;
    definition.textures = textures;
    
    definition.vertex_shader_file = string_copy(vertex_file_buffer);
    definition.fragment_shader_file = string_copy(fragment_file_buffer);
    
    fclose(file);

    return definition;
}

void parse_full_shader(const char *file_name) {
    FILE *file = fopen(file_name, "rb");
    
    if (!file) {
        return;
    }
    
    CREATE_TEMP_STR_BUFFER();
    char fragment_buffer_arr[1024];
    char *fragment_buffer = (char *) fragment_buffer_arr;

    char vertex_buffer_arr[1024];
    char *vertex_buffer = (char *) vertex_buffer_arr;
    
    while (!feof(file)) {
        fscanf(file, "%s", TEMP_BUFFER);
        if (strcmp(TEMP_BUFFER, "#start_vertex") == 0) {
            while (true) {
                fscanf(file, "%s[^\n]", TEMP_BUFFER);
                if (strcmp(TEMP_BUFFER, "#end_vertex") != 0) {
                    strcpy(vertex_buffer, TEMP_BUFFER);
                    vertex_buffer += strlen(TEMP_BUFFER);
                    *vertex_buffer = ' ';
                    vertex_buffer++;
                } else {
                    break;
                }
            }
        } else if (strcmp(TEMP_BUFFER, "#start_fragment") == 0) {
            
            while (true) {
                fscanf(file, "%s[^\n]", TEMP_BUFFER);
                if (strcmp(TEMP_BUFFER, "#end_fragment") != 0) {
                    strcpy(fragment_buffer, TEMP_BUFFER);
                    fragment_buffer += strlen(TEMP_BUFFER);
                    *fragment_buffer = ' ';
                    fragment_buffer++;
                } else {
                    break;
                }
            }
        }
    }
    
    printf("\n%s\n", vertex_buffer_arr);
    printf("\n%s\n", fragment_buffer_arr);
}