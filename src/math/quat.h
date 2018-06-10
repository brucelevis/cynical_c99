//
// Created by temdisponivel on 24/05/2018.
//

INLINE void quat_identity(quat_t *dest) {
    vec4_set(0, 0, 0, 1, dest);
}

INLINE void quat_angle_axis(const vec3_t *axis, float angle, quat_t *dest) {
    vec3_t k;
    float a, c, s;

    a = angle * 0.5f;
    c = cosf(a);
    s = sinf(a);

    vec3_normalize(axis, &k);

    dest->x = s * k.x;
    dest->y = s * k.y;
    dest->z = s * k.z;
    dest->w = c;
}

INLINE void quat_conjugate(const quat_t *a, quat_t *dest) {
    vec4_inv(a, dest);
    dest->w = -dest->w;
}

INLINE void quat_multiply(const quat_t *a, const quat_t *b, quat_t *dest) {
    dest->x = a->w * b->x + a->x * b->w + a->y * b->z - a->z * b->y;
    dest->y = a->w * b->y - a->x * b->z + a->y * b->w + a->z * b->x;
    dest->z = a->w * b->z + a->x * b->y - a->y * b->x + a->z * b->w;
    dest->w = a->w * b->w - a->x * b->x - a->y * b->y - a->z * b->z;
}

INLINE void quat_to_mat4(const quat_t *a, mat4_t *dest) {
    float w, x, y, z,
            xx, yy, zz,
            xy, yz, xz,
            wx, wy, wz, norm, s;

    norm = vec4_len(a);
    s = norm > 0.0f ? 2.0f / norm : 0.0f;

    x = a->x;
    y = a->y;
    z = a->z;
    w = a->w;

    xx = s * x * x;
    xy = s * x * y;
    wx = s * w * x;
    yy = s * y * y;
    yz = s * y * z;
    wy = s * w * y;
    zz = s * z * z;
    xz = s * x * z;
    wz = s * w * z;

    dest->x.x = 1.0f - yy - zz;
    dest->y.y = 1.0f - xx - zz;
    dest->z.z = 1.0f - xx - yy;

    dest->x.y = xy + wz;
    dest->y.z = yz + wx;
    dest->z.x = xz + wy;

    dest->y.x = xy - wz;
    dest->z.y = yz - wx;
    dest->x.z = xz - wy;

    dest->x.w = 0.0f;
    dest->y.w = 0.0f;
    dest->z.w = 0.0f;
    dest->w.x = 0.0f;
    dest->w.y = 0.0f;
    dest->w.z = 0.0f;
    dest->w.w = 1.0f;
}

INLINE void quat_to_mat4_transposed(const quat_t *a, mat4_t *dest) {
    float w, x, y, z,
            xx, yy, zz,
            xy, yz, xz,
            wx, wy, wz, norm, s;

    norm = vec4_len(a);
    s = norm > 0.0f ? 2.0f / norm : 0.0f;

    x = a->x;
    y = a->y;
    z = a->z;
    w = a->w;

    xx = s * x * x;
    xy = s * x * y;
    wx = s * w * x;
    yy = s * y * y;
    yz = s * y * z;
    wy = s * w * y;
    zz = s * z * z;
    xz = s * x * z;
    wz = s * w * z;

    dest->x.x = 1.0f - yy - zz;
    dest->y.y = 1.0f - xx - zz;
    dest->z.z = 1.0f - xx - yy;

    dest->y.x = xy + wz;
    dest->z.y = yz + wx;
    dest->x.z = xz + wy;

    dest->x.y = xy - wz;
    dest->y.z = yz - wx;
    dest->z.x = xz - wy;

    dest->x.w = 0.0f;
    dest->y.w = 0.0f;
    dest->z.w = 0.0f;
    dest->w.x = 0.0f;
    dest->w.y = 0.0f;
    dest->w.z = 0.0f;
    dest->w.w = 1.0f;
}


INLINE void quat_lerp(const quat_t *a, const quat_t *b, float t, quat_t *dest) {
    vec4_lerp(a, b, t, dest);
}

INLINE void quat_slerp(const quat_t *a, const quat_t *b, float t, quat_t *dest) {
    vec4_t q1, q2;
    float cosTheta, sinTheta, angle;

    cosTheta = vec4_dot(a, b);
    vec4_cpy(a, &q1);

    if (fabsf(cosTheta) >= 1.0f) {
        vec4_cpy(&q1, dest);
        return;
    }

    if (cosTheta < 0.0f) {
        vec4_inv(&q1, &q1);
        cosTheta = -cosTheta;
    }

    sinTheta = sqrtf(1.0f - cosTheta * cosTheta);

    /* LERP to avoid zero division */
    if (fabsf(sinTheta) < 0.001f) {
        quat_lerp(a, b, t, dest);
        return;
    }

    /* SLERP */
    angle = acosf(cosTheta);
    vec4_scale(&q1, sinf((1.0f - t) * angle), &q1);
    vec4_scale(a, sinf(t * angle), &q2);

    vec4_add(&q1, &q2, &q1);
    vec4_scale(&q1, 1.0f / sinTheta, dest);
}

INLINE void quat_look_to_mat(const vec3_t *position, const quat_t *rotation, mat4_t *dest) {
    vec4_t t;

    /* orientation */
    quat_to_mat4_transposed(rotation, dest);

    /* translate */
    vec4_set(position->x, position->y, position->z, 1.0f, &t);
    mat4_mul_vec4(dest, &t, &t);
    vec4_inv(&t, &dest->y);
}

INLINE void quat_rotate_matrix(const mat4_t *mat, const quat_t *rotation, mat4_t *dest) {
    mat4_t rot;
    quat_to_mat4(rotation, &rot);
    mat4_mul(mat, &rot, dest);
}

INLINE void quat_rotate_vec3(const vec3_t *v, const quat_t *rotation, vec3_t *dest) {
    quat_t p;
    vec3_t   u, v1, v2;
    float  s;

    quat_normalize(rotation, &p);
    vec3_set(p.x, p.y, p.z, &u);
    s = p.w;

    vec3_scale(&u, 2.0f * vec3_dot(&u, v), &v1);
    vec3_scale(v, s * s - vec3_dot(&u, &u), &v2);
    vec3_add(&v1, &v2, &v1);

    vec3_cross(&u, v, &v2);
    vec3_scale(&v2, 2.0f * s, &v2);

    vec3_add(&v1, &v2, dest);
}

INLINE void quat_look_rotation(const vec3_t *dir, const vec3_t *forward, const vec3_t *up, quat_t *dest) {
    vec3_t  axis;
    float dot, angle;

    dot = vec3_dot(dir, forward);
    if (fabsf(dot + 1.0f)  < 0.000001f) {
        vec4_set(up->x, up->y, up->z, PI, dest);
        return;
    }

    if (fabsf(dot - 1.0f) < 0.000001f) {
        vec4_set(0, 0, 0, 1, dest);
        return;
    }

    angle = acosf(dot);
    vec3_cross(forward, dir, &axis);
    vec3_normalize(&axis, &axis);
    
    quat_angle_axis(&axis, angle, dest);
}

INLINE void quat_look_from_to(const vec3_t *from, const vec3_t *to, const vec3_t *forward, const vec3_t *up, quat_t *dest) {
    vec3_t dir;
    vec3_sub(to, from, &dir);
    quat_look_rotation(&dir, forward, up, dest);
}

INLINE void quat_normalize(const quat_t *a, quat_t *dest) {
    float dot;

    dot = vec4_dot(a, a);

    if (dot <= 0.0f) {
        vec4_set(0, 0, 0, 1, dest);
        return;
    }

    vec4_scale(a, 1.0f / sqrtf(dot), dest);
}