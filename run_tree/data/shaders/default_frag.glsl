#version 150

uniform sampler2D main_texture;
uniform sampler2D bump_map_texture;
uniform float offset;

in vec2 main_texture_uv; 

out vec4 color;

void main() {
    vec4 main_tex = texture(main_texture, main_texture_uv * offset);
    vec4 bump_tex = texture(bump_map_texture, main_texture_uv * offset);
    
    color = mix(main_tex, bump_tex, .5);
}