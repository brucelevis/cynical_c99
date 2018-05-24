#version 150

uniform mat4 MVP;

in vec3 position;
in vec2 uv;
in vec4 color;

out vec4 frag_color;

void main() {
    gl_Position = vec4(position, 1) * MVP;
    frag_color = color;//vec4(uv, 1, 1);
}