#include both data/shaders/common.inc
#include vertex data/shaders/vert_include.inc
#include fragment data/shaders/frag_include.inc

#start_vertex

void main() {
    gl_Position = POS_TO_WORLD();
    main_texture_uv = uv;
}

#end_vertex

#start_fragment

void main() {
    default_frag();
}

#end_fragment