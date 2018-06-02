#start_vertex

#version 150

uniform mat4 MVP;
uniform sampler2D main_texture;

uniform vec2 sprite_offset;
uniform vec2 sprite_size;

in vec3 position;
in vec4 color;
in vec2 uv;

out vec4 vert_color;
out vec2 vert_uv;

void main() {
    const int BOTTOM_LEFT_INDEX = 0;
    const int BOTTOM_RIGHT_INDEX = 1;
    const int TOP_RIGHT_INDEX = 2;
    const int TOP_LEFT_INDEX = 3;
    
    gl_Position = MVP * vec4(position, 1);
    
    vec2 result_uv;
    if (gl_VertexID == BOTTOM_LEFT_INDEX) {
        result_uv = sprite_offset;
    } else if (gl_VertexID == BOTTOM_RIGHT_INDEX) {
        result_uv = sprite_offset;
        result_uv.x += sprite_size.x;
    } else if (gl_VertexID == TOP_RIGHT_INDEX) {
        result_uv = sprite_offset + sprite_size;
    } else if (gl_VertexID == TOP_LEFT_INDEX) {
        result_uv = sprite_offset;
        result_uv.y += sprite_size.y;
    }

    vert_color = color;
    vert_uv = result_uv;
}

#end_vertex

#start_fragment

#version 150

uniform sampler2D main_texture;
uniform vec2 tint_color;

in vec4 vert_color;
in vec2 vert_uv;

out vec4 out_color;

void main() {
    out_color = texture(main_texture, vert_uv);
    out_color.xy = out_color.xy * tint_color;
}

#end_fragment