//
// Created by temdisponivel on 24/05/2018.
//

INLINE vec4_t vec4_make(float x, float y, float z, float w) {
    vec4_t dest;
    vec4_set(x, y, z, w, &dest);
    return dest;
}

INLINE void vec4_set(float x, float y, float z, float w, vec4_t *dest) {
    dest->x = x;
    dest->y = y;
    dest->z = z;
    dest->w = w;
}

INLINE void vec4_cpy(const vec4_t *src, vec4_t *dest) {
    dest->x = src->x;
    dest->y = src->y;
    dest->z = src->z;
    dest->w = src->w;
}

INLINE void vec4_add(const vec4_t *a, const vec4_t *b, vec4_t *dest) {
    dest->x = a->x + b->x;
    dest->y = a->y + b->y;
    dest->z = a->z + b->z;
    dest->w = a->w + b->w;
}

INLINE void vec4_sub(const vec4_t *a, const vec4_t *b, vec4_t *dest) {
    dest->x = a->x - b->x;
    dest->y = a->y - b->y;
    dest->z = a->z - b->z;
    dest->w = a->w - b->w;
}

INLINE void vec4_scale(const vec4_t *a, float scalar, vec4_t *dest) {
    dest->x = a->x * scalar;
    dest->y = a->y * scalar;
    dest->z = a->z * scalar;
    dest->w = a->w * scalar;
}

INLINE void vec4_divide(const vec4_t *a, float divider, vec4_t *dest) {
    dest->x = a->x / divider;
    dest->y = a->y / divider;
    dest->z = a->z / divider;
    dest->w = a->w / divider;
}

INLINE void vec4_multiply(const vec4_t *a, const vec4_t *b, vec4_t *dest) {
    dest->x = a->x * b->x;
    dest->y = a->y * b->y;
    dest->z = a->z * b->z;
    dest->w = a->w * b->w;
}

INLINE void vec4_divide_vec4(const vec4_t *a, const vec4_t *b, vec4_t *dest) {
    dest->x = a->x / b->x;
    dest->y = a->y / b->y;
    dest->z = a->z / b->z;
    dest->w = a->w / b->w;
}

INLINE void vec4_normalize(const vec4_t *a, vec4_t *dest) {
    float len = vec4_len(a);
    vec4_set(a->x / len, a->y / len, a->z / len, a->w / len, dest);
}

INLINE float vec4_len(const vec4_t *a) {
    float sqrd_len = vec4_sqrd_len(a);
    return sqrtf(sqrd_len);
}

INLINE float vec4_sqrd_len(const vec4_t *a) {
    return vec4_dot(a, a);
}

INLINE float vec4_distance(const vec4_t *a, const vec4_t *b) {
    float sqrd_dist = vec4_sqrd_distance(a, b);
    return sqrtf(sqrd_dist);
}

INLINE float vec4_sqrd_distance(const vec4_t *a, const vec4_t *b) {
    vec4_t sub;
    vec4_sub(a, b, &sub);
    float len = vec4_sqrd_len(&sub);
    return len;
}

INLINE void vec4_max(const vec4_t *a, const vec4_t *b, vec4_t *dest) {
    float x_max = fmaxf(a->x, b->x);
    float y_max = fmaxf(a->y, b->y);
    float z_max = fmaxf(a->z, b->z);
    float w_max = fmaxf(a->w, b->w);
    vec4_set(x_max, y_max, z_max, w_max, dest);
}

INLINE void vec4_min(const vec4_t *a, const vec4_t *b, vec4_t *dest) {
    float x_min = fminf(a->x, b->x);
    float y_min = fminf(a->y, b->y);
    float z_min = fminf(a->z, b->z);
    float w_min = fmaxf(a->w, b->w);
    vec4_set(x_min, y_min, z_min, w_min, dest);
}

INLINE float vec4_dot(const vec4_t *a, const vec4_t *b) {
    return (a->x * b->x) + (a->y * b->y) + (a->z * b->z) + (a->w * b->w);
}

INLINE float vec4_inv(const vec4_t *a, vec4_t *dest) {
    dest->x = -a->x;
    dest->y = -a->y;
    dest->z = -a->z;
    dest->w = -a->w;
}

INLINE void vec4_lerp(const vec4_t *a, const vec4_t *b, float t, vec4_t *dest) {
    vec4_t diff;
    vec4_sub(a, b, &diff);
    vec4_scale(&diff, t, dest);
    vec4_add(dest, a, dest);
}