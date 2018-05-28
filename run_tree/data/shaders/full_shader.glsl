#name full_shader

#start_vertex

#version 150

uniform mat4 MVP;

in vec3 position;
in vec2 uv;
in vec4 color;

out vec2 main_texture_uv;

void main() {
    gl_Position = vec4(position, 1) * MVP;
    main_texture_uv = uv;
}

#end_vertex

#start_fragment

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

#end_fragment