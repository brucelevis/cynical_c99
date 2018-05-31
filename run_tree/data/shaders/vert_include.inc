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
