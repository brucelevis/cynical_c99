//
// Created by temdisponivel on 24/05/2018.
//

INLINE vec2_t vec2_make(float x, float y) {
    vec2_t dest;
    vec2_set(x, y, &dest);
    return dest;
}

INLINE void vec2_set(float x, float y, vec2_t *dest) {
    dest->x = x;
    dest->y = y;
}

INLINE void vec2_cpy(const vec2_t *src, vec2_t *dest) {
    dest->x = src->x;
    dest->y = src->y;
}

INLINE void vec2_add(const vec2_t *a, const vec2_t *b, vec2_t *dest) {
    dest->x = a->x + b->x;
    dest->y = a->y + b->y;
}

INLINE void vec2_sub(const vec2_t *a, const vec2_t *b, vec2_t *dest) {
    dest->x = a->x - b->x;
    dest->y = a->y - b->y;
}

INLINE void vec2_scale(const vec2_t *a, float scalar, vec2_t *dest) {
    dest->x = a->x * scalar;
    dest->y = a->y * scalar;
}

INLINE void vec2_divide(const vec2_t *a, float divider, vec2_t *dest) {
    dest->x = a->x / divider;
    dest->y = a->y / divider;
}

INLINE void vec2_multiply(const vec2_t *a, const vec2_t *b, vec2_t *dest) {
    dest->x = a->x * b->x;
    dest->y = a->y * b->y;
}

INLINE void vec2_divide_vec2(const vec2_t *a, const vec2_t *b, vec2_t *dest) {
    dest->x = a->x / b->x;
    dest->y = a->y / b->y;
}

INLINE void vec2_normalize(const vec2_t *a, vec2_t *dest) {
    float len = vec2_len(a);
    vec2_set(a->x / len, a->y / len, dest);
}

INLINE float vec2_len(const vec2_t *a) {
    float sqrd_len = vec2_sqrd_len(a);
    return sqrtf(sqrd_len);
}

INLINE float vec2_sqrd_len(const vec2_t *a) {
    return vec2_dot(a, a);
}

INLINE float vec2_distance(const vec2_t *a, const vec2_t *b) {
    float sqrd_dist = vec2_sqrd_distance(a, b);
    return sqrtf(sqrd_dist);
}

INLINE float vec2_sqrd_distance(const vec2_t *a, const vec2_t *b) {
    vec2_t sub;
    vec2_sub(a, b, &sub);
    float len = vec2_sqrd_len(&sub);
    return len;
}

INLINE void vec2_max(const vec2_t *a, const vec2_t *b, vec2_t *dest) {
    float x_max = fmaxf(a->x, b->x);
    float y_max = fmaxf(a->y, b->y);
    vec2_set(x_max, y_max, dest);
}

INLINE void vec2_min(const vec2_t *a, const vec2_t *b, vec2_t *dest) {
    float x_min = fminf(a->x, b->x);
    float y_min = fminf(a->y, b->y);
    vec2_set(x_min, y_min, dest);
}

INLINE float vec2_dot(const vec2_t *a, const vec2_t *b) {
    return (a->x * b->x) + (a->y * b->y);
}