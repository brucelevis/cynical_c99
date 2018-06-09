
INLINE rect_t rect_make(const vec2_t *bottom_left, const vec2_t *size) {
    rect_t dest;
    rect_set(bottom_left, size, &dest);
    return dest;
}

INLINE void rect_set(const vec2_t *bottom_left, const vec2_t *size, rect_t *rect) {
    vec2_cpy(bottom_left, &rect->bottom_left);
    vec2_cpy(size, &rect->size);
}

// TODO(temdisponivel): Make this thing work regardless of the order of the parameters
INLINE bool rect_touch(const rect_t *a, const rect_t *b) {
    vec2_t a_half_size;
    vec2_scale(&a->size, .5f, &a_half_size);
    
    vec2_t b_half_size;
    vec2_scale(&b->size, .5f, &b_half_size);
    
    vec2_t a_center;
    vec2_add(&a->bottom_left, &a_half_size, &a_center); 

    vec2_t b_center;
    vec2_add(&b->bottom_left, &b_half_size, &b_center);
    
    vec2_t diff;
    vec2_sub(&a_center, &b_center, &diff);
    
    float x_distance = diff.x;
    float y_distance = diff.y;

    x_distance = fabsf(x_distance);
    y_distance = fabsf(y_distance);
    
    float both_width = (a_half_size.width + b_half_size.width);
    float both_height = (a_half_size.height + b_half_size.height);
    
    if (x_distance < both_width && y_distance < both_height) {
        return true;
    } else {
        return false;
    }
}

INLINE vec2_t rect_get_top_right(const rect_t *a) {
    return vec2_make(a->bottom_left.x + a->size.x, a->bottom_left.y + a->size.y);
}