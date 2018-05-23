#version 150

out vec4 color;
in vec4 frag_color;

void main() {
    color = frag_color;//vec4(0, 1, 0, 1);
}