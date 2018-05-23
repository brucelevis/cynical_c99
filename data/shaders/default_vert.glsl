#version 150

in vec3 position;
in vec2 uv;
in vec4 color;

out vec4 frag_color;

void main() {
    gl_Position = vec4(position, 1);
    frag_color = vec4(uv, 1, 1);
}