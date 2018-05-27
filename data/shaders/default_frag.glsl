#version 150

uniform sampler2D main_texture;
in vec2 main_texture_uv;

out vec4 color;

void main() {
    color = texture(main_texture, main_texture_uv);
}