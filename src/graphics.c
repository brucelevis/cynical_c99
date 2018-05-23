//
// Created by Firehorse on 22/05/2018.
//

#include "graphics.h"

shader_t create_shader(const char *vertex, const char *fragment) {
    uint program = glCreateProgram();
    uint vert_handle = glCreateShader(GL_VERTEX_SHADER);
    uint frag_handle = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vert_handle, 1, &vertex, null);
    glCompileShader(vert_handle);

    check_shader_compilation(vert_handle);

    glShaderSource(frag_handle, 1, &fragment, null);
    glCompileShader(frag_handle);

    check_shader_compilation(frag_handle);

    glAttachShader(program, vert_handle);
    glAttachShader(program, frag_handle);

    // TODO(temdisponivel): bind uniform locations

    glLinkProgram(program);

    check_program_linkage(program);

    glDeleteShader(vert_handle);
    glDeleteShader(frag_handle);

    check_gl_error();

    shader_t shader;
    shader.handle = program;
    return shader;
}

