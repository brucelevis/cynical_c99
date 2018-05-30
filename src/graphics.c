//
// Created by Firehorse on 22/05/2018.
//

#include <malloc.h>

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

#undef STB_IMAGE_IMPLEMENTATION

#include "graphics.h"
#include "resources.h"
#include "hot_reloader.h"
#include "file.h"

void reload_shader_sources(
        uint handle, 
        const char *shader_file,
        char *both_include_file_path,
        char *vert_include_file_path,
        char *frag_include_file_path
) {
    
    CREATE_TEMP_NAMED_STR_BUFFER(vertex_buffer);
    CLEAR_TEMP_NAMED_STR_BUFFER(vertex_buffer);

    CREATE_TEMP_NAMED_STR_BUFFER(fragment_buffer);
    CLEAR_TEMP_NAMED_STR_BUFFER(fragment_buffer);

    bool read_shader = read_shader_file(
            shader_file, 
            vertex_buffer, 
            fragment_buffer,
            both_include_file_path,
            vert_include_file_path,
            frag_include_file_path
    );

    ASSERT(read_shader);   

    update_shader_program(handle, vertex_buffer, fragment_buffer);
}

shader_t create_shader_from_file(const char *shader_file) {

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

    shader_t shader;
    shader.handle = program;
    return shader;
}

void update_shader_program(uint program, const char *vertex, const char *fragment) {
    {
        // TODO(temdisponivel): Should we cache this shader IDs in order to detach them later
        // instead of asking for the program for its shaders?!

        uint shaders[2];
        int count;
        glGetAttachedShaders(program, 2, &count, shaders);

        if (count > 0) {
            glDetachShader(program, shaders[0]);
            glDetachShader(program, shaders[1]);
        }
    }
    
    uint vert_handle = glCreateShader(GL_VERTEX_SHADER);
    uint frag_handle = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vert_handle, 1, &vertex, null);
    glCompileShader(vert_handle);

    CHECK_SHADER_COMPILATION(vert_handle);

    glShaderSource(frag_handle, 1, &fragment, null);
    glCompileShader(frag_handle);

    CHECK_SHADER_COMPILATION(frag_handle);

    glAttachShader(program, vert_handle);
    glAttachShader(program, frag_handle);

    glBindAttribLocation(program, VERT_POS_INDEX, VERT_POS_NAME);
    glBindAttribLocation(program, VERT_UV_INDEX, VERT_UV_NAME);
    glBindAttribLocation(program, VERT_COLOR_INDEX, VERT_COLOR_NAME);

    glLinkProgram(program);

    CHECK_PROGRAM_LINKAGE(program);

    glDeleteShader(vert_handle);
    glDeleteShader(frag_handle);

    CHECK_GL_ERROR();
}

void destroy_shader(shader_t shader) {
    stop_watch_shader_file(shader.handle);
    glDeleteProgram(shader.handle);
}

model_t create_quad() {
    const int QUAD_VERT_COUNT = 4;
    const int QUAD_INDEX_COUNT = 6;

    float *vertices = malloc(FULL_MODEL_BYTE_SIZE(QUAD_VERT_COUNT));

    vec3_t *positions = (vec3_t *) vertices;
    vec2_t *uvs = (vec2_t *) (((void *) positions) + UV_BYTE_OFFSET(4));
    vec4_t *colors = (vec4_t *) (((void *) positions) + COLOR_BYTE_OFFSET(4));

    vec3_set(-1, -1, 0, &positions[0]);
    VEC2_SET_ZERO(&uvs[0]);
    COLOR_SET_RED(&colors[0]);

    vec3_set(1, -1, 0, &positions[1]);
    VEC2_SET_RIGH(&uvs[1]);
    COLOR_SET_GREEN(&colors[1]);

    vec3_set(1, 1, 0, &positions[2]);
    VEC2_SET_ONE(&uvs[2]);
    COLOR_SET_BLUE(&colors[2]);

    vec3_set(-1, 1, 0, &positions[3]);
    VEC2_SET_UP(&uvs[3]);
    COLOR_SET_YELLOW(&colors[3]);

    uint *index = malloc(sizeof(uint) * QUAD_INDEX_COUNT);
    index[0] = 0;
    index[1] = 1;
    index[2] = 2;
    index[3] = 0;
    index[4] = 3;
    index[5] = 2;

    model_t model;
    model.full_vertices_data = vertices;
    model.positions_ptr_offset = positions;
    model.uvs_ptr_offset = uvs;
    model.colors_ptr_offset = colors;
    model.vertices_count = QUAD_VERT_COUNT;
    model.indexes = index;
    model.indexes_count = QUAD_INDEX_COUNT;
    return model;
}

void destroy_model(model_t model) {
    free(model.full_vertices_data);
    if (model.indexes) {
        free(model.indexes);
    }
}

#ifdef DEV

void print_model(model_t model) {

    for (int i = 0; i < model.vertices_count; ++i) {
        vec3_t pos = model.positions_ptr_offset[i];
        vec2_t uv = model.uvs_ptr_offset[i];
        vec4_t color = model.colors_ptr_offset[i];

        printf(
                "x: %f y: %f z: %f - r: %f g: %f b: %f a: %f - u: %f v: %f \n",
                pos.x, pos.y, pos.z,
                color.r, color.g, color.b, color.a,
                uv.x, uv.y
        );
    }
}

#endif

mesh_t create_mesh(model_t model) {
    uint vao;
    uint vbo;
    uint vio = 0;

    const int full_model_size = FULL_MODEL_BYTE_SIZE(model.vertices_count);
    const int pos_offset = POS_BYTE_OFFSET(model.vertices_count);
    const int uv_offset = UV_BYTE_OFFSET(model.vertices_count);
    const int color_offset = COLOR_BYTE_OFFSET(model.vertices_count);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(
            GL_ARRAY_BUFFER,
            full_model_size,
            model.full_vertices_data,
            GL_STATIC_DRAW
    );
    CHECK_GL_ERROR();

    glVertexAttribPointer(
            VERT_POS_INDEX,
            POS_DIMENTION,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void *) pos_offset
    );

    glVertexAttribPointer(
            VERT_UV_INDEX,
            UV_DIMENTION,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void *) uv_offset
    );

    glVertexAttribPointer(
            VERT_COLOR_INDEX,
            COLOR_DIMENTION,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void *) color_offset
    );
    CHECK_GL_ERROR();

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    if (model.indexes_count) {
        glGenBuffers(1, &vio);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vio);

        glBufferData(
                GL_ELEMENT_ARRAY_BUFFER,
                sizeof(uint) * model.indexes_count,
                model.indexes,
                GL_STATIC_DRAW
        );

        CHECK_GL_ERROR();

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    mesh_t mesh;
    mesh.vao = vao;
    mesh.vbo = vbo;
    mesh.vio = vio;

    if (vio) {
        mesh.elements_len = model.indexes_count;
    } else {
        mesh.elements_len = model.vertices_count;
    }

    return mesh;
}

void destroy_mesh(mesh_t mesh) {

    glDeleteBuffers(1, &mesh.vbo);

    if (mesh.vio) {
        glDeleteBuffers(1, &mesh.vio);
    }

    glDeleteVertexArrays(1, &mesh.vao);

    CHECK_GL_ERROR();

    // TODO(temdisponivel): should we set these handles to invalid values?!
}

void draw_mesh(mesh_t mesh) {
    glBindVertexArray(mesh.vao);
    glEnableVertexAttribArray(VERT_POS_INDEX);
    glEnableVertexAttribArray(VERT_UV_INDEX);
    glEnableVertexAttribArray(VERT_COLOR_INDEX);

    if (mesh.vio) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vio);

        glDrawElements(GL_TRIANGLE_FAN, mesh.elements_len, GL_UNSIGNED_INT, null);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    } else {
        glDrawArrays(GL_TRIANGLE_FAN, 0, mesh.elements_len);
    }

    CHECK_GL_ERROR();

    glDisableVertexAttribArray(VERT_COLOR_INDEX);
    glDisableVertexAttribArray(VERT_UV_INDEX);
    glDisableVertexAttribArray(VERT_POS_INDEX);
    glBindVertexArray(0);
}

bool load_image_from_file(const char *image_file, image_t *dest) {

    // TODO(temdisponivel): Create a buffer in order to prevent allocations
    uint len;
    byte *file_data = read_file_data_alloc(image_file, &len);

#if DEV
    if (!file_data) {
        file_data = read_file_data_alloc(DEFAULT_IMAGE_FILE_PATH, &len);
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

    image_t img;
    strcpy(img.file_path, image_file);
    img.data = image_data;
    img.size = vec2_make(width, height);
    *dest = img;
    return true;
}

void destroy_image(const image_t *image) {
    stbi_image_free(image->data);
}

void create_texture_from_file(const char *file_path, texture_t *dest) {
    image_t img;
    bool loaded = load_image_from_file(file_path, &img);
    ASSERT(loaded);
    create_texture(&img, dest);
    destroy_image(&img);
}

void create_texture(const image_t *image, texture_t *dest) {
    uint handle;
    glGenTextures(1, &handle);

    update_texture_data(handle, image);

    watch_texture_file(handle, image->file_path);

    dest->handle = handle;
}

void reload_texture(uint handle, const char *file_path) {
    image_t img;
    bool loaded = load_image_from_file(file_path, &img);
    ASSERT(loaded);
    update_texture_data(handle, &img);
    destroy_image(&img);
}

void update_texture_data(uint handle, const image_t *image) {
    glBindTexture(GL_TEXTURE_2D, handle);

    glTexImage2D(
            GL_TEXTURE_2D,
            0, // Mip map level
            GL_RGBA,
            (uint) image->size.x,
            (uint) image->size.y,
            0, // border
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            image->data
    );
    CHECK_GL_ERROR();

    // TODO: parameterize this
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    CHECK_GL_ERROR();

    glBindTexture(GL_TEXTURE_2D, 0);

    CHECK_GL_ERROR();
}

void destroy_texture(const texture_t *texture) {
    glDeleteTextures(1, &texture->handle);
    stop_watch_texture_file(texture->handle);
}

void create_material_from_file(const char *file_path, material_t *dest) {
    reload_material(file_path, dest);
    watch_material_definition_file(dest, file_path);
}

// TODO(temdisponivel): Make sure to not call this function from create_material_from_file
void reload_material(const char *file_path, material_t *dest) {
    // TODO(temdisponivel): FIX ME
    // TODO(temdisponivel): FIX ME
    // TODO(temdisponivel): FIX ME
    
    /*
    destroy_shader(dest->shader);

    for (int i = 0; i < dest->texture_uniforms_len; ++i) {
        destroy_texture(&dest->texture_uniforms[i].texture);
    }
     */
    
    material_definition_t definition = {};
    
    bool read = read_material_definition_file(file_path, &definition);
    ASSERT(read);
    create_material(&definition, dest);
}

void create_material(const material_definition_t *definition, material_t *dest) {

    shader_t shader = create_shader_from_file(definition->shader_file);

    dest->shader = shader;

    dest->float_uniforms_len = definition->floats_len;
    ASSERT(dest->float_uniforms_len < MAX_FLOATS);

    dest->mat4_uniforms_len = definition->mat4s_len;
    ASSERT(dest->mat4_uniforms_len < MAX_MAT4S);

    dest->texture_uniforms_len = definition->textures_len;
    ASSERT(dest->texture_uniforms_len < MAX_TEXTURES);

    // ============= FLOAT

    for (int i = 0; i < definition->floats_len; ++i) {
        float_uniform_definition_t float_def = definition->floats[i];

        float_uniform_t float_uni;
        strcpy(float_uni.info.name, float_def.uniform_name);

        float_uni.value = float_def.default_value;

        dest->float_uniforms[i] = float_uni;
    }

    // ============= MAT 4

    for (int i = 0; i < definition->mat4s_len; ++i) {
        mat4_uniform_definition_t mat4_def = definition->mat4s[i];

        mat4_uniform_t mat4_uni;
        strcpy(mat4_uni.info.name, mat4_def.uniform_name);
        mat4_uni.value = mat4_def.default_value;

        dest->mat4_uniforms[i] = mat4_uni;
    }

    // ============= TEXTURE

    for (int i = 0; i < definition->textures_len; ++i) {
        texture_uniform_definition_t tex_def = definition->textures[i];

        texture_uniform_t tex_uni;
        strcpy(tex_uni.info.name, tex_def.uniform_name);

        tex_uni.texture_unit = TEXTURE_UNIT_0 + i;

        char *file_path;
        if (strlen(tex_def.image_file_name)) {
            file_path = tex_def.image_file_name;
        } else {
            file_path = DEFAULT_IMAGE_FILE_PATH;
        }

        create_texture_from_file(file_path, &tex_uni.texture);

        dest->texture_uniforms[i] = tex_uni;
    }
}

void destroy_material(const material_t *material) {
    destroy_shader(material->shader);

    for (int i = 0; i < material->texture_uniforms_len; ++i) {
        texture_uniform_t texture_uni = material->texture_uniforms[i];
        destroy_texture(&texture_uni.texture);
    }
    
    stop_watch_material_definition_file(material);
}

void use_material(const material_t *material) {
    glUseProgram(material->shader.handle);
    CHECK_GL_ERROR();

    for (int i = 0; i < material->float_uniforms_len; ++i) {
        float_uniform_t uniform = material->float_uniforms[i];
        int loc = glGetUniformLocation(material->shader.handle, uniform.info.name);
        if (loc >= 0) {
            glUniform1f(loc, uniform.value);
        }
    }

    CHECK_GL_ERROR();

    for (int i = 0; i < material->mat4_uniforms_len; ++i) {
        mat4_uniform_t uniform = material->mat4_uniforms[i];
        int loc = glGetUniformLocation(material->shader.handle, uniform.info.name);
        if (loc >= 0) {
            glUniformMatrix4fv(loc, 1, GL_FALSE, &uniform.value);
        }
    }

    CHECK_GL_ERROR();

    for (int i = 0; i < material->texture_uniforms_len; ++i) {
        texture_uniform_t uniform = material->texture_uniforms[i];
        int loc = glGetUniformLocation(material->shader.handle, uniform.info.name);
        if (loc >= 0) {
            glActiveTexture(uniform.texture_unit);
            glBindTexture(GL_TEXTURE_2D, uniform.texture.handle);
            glUniform1i(loc, uniform.texture_unit - TEXTURE_UNIT_0);
        }
    }

    CHECK_GL_ERROR();

    // TODO(temdisponivel): Should I create a function that will unbind all these uniforms?!
}