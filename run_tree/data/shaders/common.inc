#version 150

uniform mat4 MVP;
uniform sampler2D main_texture;
uniform sampler2D bump_map_texture;
uniform sampler2D yellow_texture;
uniform float offset;

uniform vec2 relative_sprite_offset;
uniform vec2 relative_sprite_size;
