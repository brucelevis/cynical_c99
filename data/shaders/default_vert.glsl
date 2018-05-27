#version 150

uniform mat4 MVP;

in vec3 position;
in vec2 uv;
in vec4 color;

out vec2 main_texture_uv;

void main() {
    gl_Position = vec4(position, 1) * MVP;
    main_texture_uv = uv;
}