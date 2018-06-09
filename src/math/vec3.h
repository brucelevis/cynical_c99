//
// Created by temdisponivel on 23/05/2018.
//

INLINE vec3_t vec3_make(float x, float y, float z) {
    vec3_t dest;
    vec3_set(x, y, z, &dest);
    return dest;
}

INLINE void vec3_set(float x, float y, float z, vec3_t *dest) {
    dest->x = x;
    dest->y = y;
    dest->z = z;
}

INLINE void vec3_cpy(const vec3_t *src, vec3_t *dest) {
    dest->x = src->x;
    dest->y = src->y;
    dest->z = src->z;
}

INLINE void vec3_add(const vec3_t *a, const vec3_t *b, vec3_t *dest) {
    dest->x = a->x + b->x;
    dest->y = a->y + b->y;
    dest->z = a->z + b->z;
}

INLINE void vec3_sub(const vec3_t *a, const vec3_t *b, vec3_t *dest) {
    dest->x = a->x - b->x;
    dest->y = a->y - b->y;
    dest->z = a->z - b->z;
}

INLINE void vec3_scale(const vec3_t *a, float scalar, vec3_t *dest) {
    dest->x = a->x * scalar;
    dest->y = a->y * scalar;
    dest->z = a->z * scalar;
}

INLINE void vec3_scale_vec3(const vec3_t *a, const vec3_t *b, vec3_t *dest) {
    dest->x = a->x * b->x;
    dest->y = a->y * b->y;
    dest->z = a->z * b->z;
}

INLINE void vec3_divide(const vec3_t *a, float divider, vec3_t *dest) {
    dest->x = a->x / divider;
    dest->y = a->y / divider;
    dest->z = a->z / divider;
}

INLINE void vec3_multiply(const vec3_t *a, const vec3_t *b, vec3_t *dest) {
    dest->x = a->x * b->x;
    dest->y = a->y * b->y;
    dest->z = a->z * b->z;
}

INLINE void vec3_divide_vec3(const vec3_t *a, const vec3_t *b, vec3_t *dest) {
    dest->x = a->x / b->x;
    dest->y = a->y / b->y;
    dest->z = a->z / b->z;
}

INLINE void vec3_normalize(const vec3_t *a, vec3_t *dest) {
    float len = vec3_len(a);
    vec3_set(a->x / len, a->y / len, a->z / len, dest);
}

INLINE float vec3_len(const vec3_t *a) {
    float sqrd_len = vec3_sqrd_len(a);
    return sqrtf(sqrd_len);
}

INLINE float vec3_sqrd_len(const vec3_t *a) {
    return vec3_dot(a, a);
}

INLINE float vec3_distance(const vec3_t *a, const vec3_t *b) {
    float sqrd_dist = vec3_sqrd_distance(a, b);
    return sqrtf(sqrd_dist);
}

INLINE float vec3_sqrd_distance(const vec3_t *a, const vec3_t *b) {
    vec3_t sub;
    vec3_sub(a, b, &sub);
    float len = vec3_sqrd_len(&sub);
    return len;
}

INLINE void vec3_rotate(const vec3_t *v, float angle, const vec3_t *axis, vec3_t *dest) {
    vec3_t v1, v2, k;
    float c, s;

    c = cosf(angle);
    s = sinf(angle);

    vec3_normalize(axis, &k);

    vec3_scale(v, c, &v1);

    vec3_cross(&k, v, &v2);
    vec3_scale(&v2, s, &v2);

    vec3_add(&v1, &v2, &v1);

    float dot = vec3_dot(&k, v);
    vec3_scale(&k, dot * (1.0f - c), &v2);
    vec3_add(&v1, &v2, dest);
}

INLINE void vec3_max(const vec3_t *a, const vec3_t *b, vec3_t *dest) {
    float x_max = fmaxf(a->x, b->x);
    float y_max = fmaxf(a->y, b->y);
    float z_max = fmaxf(a->z, b->z);
    vec3_set(x_max, y_max, z_max, dest);
}

INLINE void vec3_min(const vec3_t *a, const vec3_t *b, vec3_t *dest) {
    float x_min = fminf(a->x, b->x);
    float y_min = fminf(a->y, b->y);
    float z_min = fminf(a->z, b->z);
    vec3_set(x_min, y_min, z_min, dest);
}

INLINE void vec3_ortho(const vec3_t *a, vec3_t *dest) {
    dest->x = a->y - a->z;
    dest->y = a->z - a->x;
    dest->z = a->x - a->y;
}

INLINE float vec3_dot(const vec3_t *a, const vec3_t *b) {
    return (a->x * b->x) + (a->y * b->y) + (a->z * b->z);
}

INLINE void vec3_cross(const vec3_t *a, const vec3_t *b, vec3_t *dest) {
    dest->x = a->y * b->z - a->z * b->y;
    dest->y = a->z * b->x - a->x * b->z;
    dest->z = a->x * b->y - a->y * b->x;
}

INLINE float vec3_angle(const vec3_t *a, const vec3_t *b) {
    float a_len = vec3_len(a);
    float b_len = vec3_len(b);

    float norm = 1.0f / (a_len * b_len);
    float dot = vec3_dot(a, b);
    
    return acosf(dot * norm);
}

INLINE float vec3_inv(const vec3_t *a, vec3_t *dest) {
    dest->x = -a->x;
    dest->y = -a->y;
    dest->z = -a->z;
}

INLINE void vec3_lerp(const vec3_t *a, const vec3_t *b, float t, vec3_t *dest) {
    vec3_t diff;
    vec3_sub(a, b, &diff);
    vec3_scale(&diff, t, dest);
    vec3_add(dest, a, dest);
}