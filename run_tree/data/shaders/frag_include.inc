in vec2 main_texture_uv; 
out vec4 color;

void default_frag() {
    vec4 main_tex = texture(main_texture, main_texture_uv * offset);
    vec4 bump_tex = texture(bump_map_texture, main_texture_uv * offset);
    vec4 yellow_tex = texture(yellow_texture, main_texture_uv * offset);
    color = main_tex;//mix(main_tex, bump_tex, .5f);
}
