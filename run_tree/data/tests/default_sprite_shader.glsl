#include both data/tests/default_uniforms.glsl

#start_vertex

in vec3 position;
in vec2 uv;
in vec4 color;

out vec2 frag_uv;

void main() {
    gl_Position = MVP * vec4(position, 1);
    frag_uv = uv;
}

#end_vertex

#start_fragment

in vec2 frag_uv;

out vec4 out_color;

void main() {
    out_color = texture(main_texture, frag_uv);
}

#end_fragment