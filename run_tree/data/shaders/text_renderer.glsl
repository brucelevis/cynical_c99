#include both data/tests/default_uniforms.glsl

#start_vertex

in vec2 uv;
in vec3 position;

out vec2 out_uv;

void main() {
    gl_Position = MVP * vec4(position, 1);
    out_uv = uv;
}

#end_vertex

#start_fragment

uniform vec4 color;

in vec2 out_uv;
out vec4 out_color;

void main() {
    out_color = texture(main_texture, out_uv);
}

#end_fragment