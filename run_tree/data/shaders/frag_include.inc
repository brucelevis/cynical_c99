in vec2 main_texture_uv; 
out vec4 color;

void default_frag() {
    vec4 main_tex = vec4(1, 1, 1, 1);// texture(main_texture, main_texture_uv * offset);
    vec4 bump_tex = texture(bump_map_texture, main_texture_uv * offset);
    color = mix(main_tex, bump_tex, .5f);
}
