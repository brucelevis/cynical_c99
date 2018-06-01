#include both data/shaders/common.inc
//#include vertex data/shaders/vert_include.inc
//#include fragment data/shaders/frag_include.inc

#start_vertex

in vec3 position;
in vec2 uv;
in vec4 color;

out vec2 main_texture_uv;

vec4 POS_TO_WORLD() {
    return MVP * vec4(position, 1);
}

vec4 TO_WORLD(vec3 vec) {
    return MVP * vec4(vec, 1);
}

void main() {

    const int BOTTOM_LEFT_INDEX = 0;
    const int BOTTOM_RIGHT_INDEX = 1;
    const int TOP_RIGHT_INDEX = 2;
    const int TOP_LEFT_INDEX = 3;
    
    gl_Position = POS_TO_WORLD();
    
    vec2 result_uv;
    if (gl_VertexID == BOTTOM_LEFT_INDEX) {
        result_uv = relative_sprite_offset;
    } else if (gl_VertexID == BOTTOM_RIGHT_INDEX) {
        result_uv = relative_sprite_offset;
        result_uv.x += relative_sprite_size.x;
    } else if (gl_VertexID == TOP_RIGHT_INDEX) {
        result_uv = relative_sprite_offset + relative_sprite_size;
    } else if (gl_VertexID == TOP_LEFT_INDEX) {
        result_uv = relative_sprite_offset;
        result_uv.y += relative_sprite_size.y;
    }
        
    main_texture_uv = result_uv;
}

#end_vertex

#start_fragment

in vec2 main_texture_uv; 
out vec4 color;

void default_frag() {
    vec4 main_tex = texture(main_texture, main_texture_uv);
    vec4 bump_tex = texture(bump_map_texture, main_texture_uv);
    vec4 yellow_tex = texture(yellow_texture, main_texture_uv);
    color = bump_tex;//mix(main_tex, bump_tex, 1.f);
}


void main() {
    default_frag();
}

#end_fragment