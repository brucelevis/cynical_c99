#include both data/shaders/common.inc
#include vertex data/shaders/vert_include.inc
#include fragment data/shaders/frag_include.inc

#start_vertex

void main() {
    default_vert();
}

#end_vertex

#start_fragment

void main() {
    default_frag();
    color = vec4(1, 0, 0, 1); 
}

#end_fragment