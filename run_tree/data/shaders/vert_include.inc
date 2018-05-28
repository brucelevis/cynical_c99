in vec3 position;
in vec2 uv;
in vec4 color;

out vec2 main_texture_uv;

void default_vert() {
    gl_Position = vec4(position, 1) * MVP;
    main_texture_uv = uv;
}
