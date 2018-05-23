#include <stdio.h>
#include "GL/glew.h"
#include "GL/GL.h"
#include "GLFW/glfw3.h"
#include "common.h"
#include "file.h"
#include "graphics.h"

#define FILE_BUFFER_SIZE 2048
byte FILE_BUFFER[FILE_BUFFER_SIZE];

int main() {
    glfwInit();

    GLFWwindow *window = glfwCreateWindow(1024, 768, "Hello world!", NULL, NULL);

    if (!window) {
        return -1;
    }

    glfwMakeContextCurrent(window);

    glewInit();

    char *vert_shader = FILE_BUFFER;
    uint len;
    file_status_t result = read_file_data(
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
    result = read_file_data(
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

    glUseProgram(shader.handle);
    check_gl_error();

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        int width, height;
        glfwGetWindowSize(window, &width, &height);
        glViewport(0, 0, width, height);

        glClearColor(255, 0, 0, 255);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}