//
// Created by Firehorse on 22/05/2018.
//

#include <malloc.h>

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

#undef STB_IMAGE_IMPLEMENTATION

#include "graphics.h"
#include "resources.h"

shader_t create_shader(const char *vertex, const char *fragment) {
    uint program = glCreateProgram();
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

    shader_t shader;
    shader.handle = program;
    return shader;
}

void destroy_shader(shader_t shader) {
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

bool load_image(const char *image_file, image_t *dest) {
    
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
    img.data = image_data;
    img.size = vec2_make(width, height);
    *dest = img;
    return true;
}

void destroy_image(const image_t *image) {
    stbi_image_free(image->data);
}

texture_t create_texture(const image_t *image) {
    uint handle;
    glGenTextures(1, &handle);

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

    texture_t texture;
    texture.handle = handle;
    return texture;
}

void destroy_texture(const texture_t *texture) {
    glDeleteTextures(1, &texture->handle);
}

material_t create_material(const material_definition_t *definition) {
    CREATE_TEMP_NAMED_STR_BUFFER(vertex_buffer);
    CREATE_TEMP_NAMED_STR_BUFFER(fragment_buffer);
    
    bool read_shader = read_shader_file(definition->shader_file, vertex_buffer, fragment_buffer);
    
    ASSERT(read_shader);
        
    shader_t shader = create_shader(
            vertex_buffer,
            fragment_buffer
    );
    
    material_t mat;
    mat.shader = shader;
    
    mat.float_uniforms_len = definition->floats_len;
    ASSERT(mat.float_uniforms_len < MAX_FLOATS);
    
    mat.mat4_uniforms_len = definition->mat4s_len;
    ASSERT(mat.mat4_uniforms_len < MAX_MAT4S);
    
    mat.texture_uniforms_len = definition->textures_len;
    ASSERT(mat.texture_uniforms_len < MAX_TEXTURES);
    
    // ============= FLOAT
    
    for (int i = 0; i < definition->floats_len; ++i) {
        float_uniform_definition_t float_def = definition->floats[i];

        float_uniform_t float_uni;
        float_uni.info.name_hash = hash_string(float_def.uniform_name);
        float_uni.info.location = glGetUniformLocation(shader.handle, float_def.uniform_name);
        
        float_uni.value = float_def.default_value;
      
        ASSERT(float_uni.info.location >= 0);

        mat.float_uniforms[i] = float_uni;
    }

    // ============= MAT 4
    
    for (int i = 0; i < definition->mat4s_len; ++i) {
        mat4_uniform_definition_t mat4_def = definition->mat4s[i];

        mat4_uniform_t mat4_uni;
        mat4_uni.info.name_hash = hash_string(mat4_def.uniform_name);
        mat4_uni.info.location = glGetUniformLocation(shader.handle, mat4_def.uniform_name);

        mat4_uni.value = mat4_def.default_value;

        ASSERT(mat4_uni.info.location >= 0);

        mat.mat4_uniforms[i] = mat4_uni;
    }

    // ============= TEXTURE
    
    for (int i = 0; i < definition->textures_len; ++i) {
        texture_uniform_definition_t tex_def = definition->textures[i];
        
        texture_uniform_t tex_uni;
        tex_uni.info.name_hash = hash_string(tex_def.uniform_name);
        tex_uni.info.location = glGetUniformLocation(shader.handle, tex_def.uniform_name);
        
        ASSERT(tex_uni.info.location >= 0);
        
        tex_uni.texture_unit = TEXTURE_UNIT_0 + i;
        
        char *file_path;
        if (strlen(tex_def.image_file_name)) {
            file_path = tex_def.image_file_name;
        } else {
            file_path = DEFAULT_IMAGE_FILE_PATH;
        }

        image_t img;
        
        bool result = load_image(file_path, &img);
        
        ASSERT(result);
        
        texture_t tex = create_texture(&img);
        tex_uni.texture = tex;
        
        mat.texture_uniforms[i] = tex_uni;
        
        destroy_image(&img);
    }

    return mat;
}

void destroy_material(const material_t *material) {
    destroy_shader(material->shader);

    for (int i = 0; i < material->texture_uniforms_len; ++i) {
        texture_uniform_t texture_uni = material->texture_uniforms[i];
        destroy_texture(&texture_uni.texture);
    }
}

void use_material(const material_t *material) {
    glUseProgram(material->shader.handle);
    CHECK_GL_ERROR();

    for (int i = 0; i < material->float_uniforms_len; ++i) {
        float_uniform_t uniform = material->float_uniforms[i];
        
        if (uniform.info.location >= 0) {
            glUniform1f(uniform.info.location, uniform.value);
        }
    }
    
    CHECK_GL_ERROR();

    for (int i = 0; i < material->mat4_uniforms_len; ++i) {
        mat4_uniform_t uniform = material->mat4_uniforms[i];

        if (uniform.info.location >= 0) {
            glUniformMatrix4fv(uniform.info.location, 1, GL_FALSE, &uniform.value);
        }
    }

    CHECK_GL_ERROR();

    for (int i = 0; i < material->texture_uniforms_len; ++i) {
        texture_uniform_t uniform = material->texture_uniforms[i];

        if (uniform.info.location >= 0) {
            glActiveTexture(uniform.texture_unit);
            glBindTexture(GL_TEXTURE_2D, uniform.texture.handle);
            glUniform1i(uniform.info.location, uniform.texture_unit - TEXTURE_UNIT_0);
        }
    }

    CHECK_GL_ERROR();
    
    // TODO(temdisponivel): Should I create a function that will unbind all these uniforms?!
}