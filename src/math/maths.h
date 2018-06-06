//
// Created by temdisponivel on 23/05/2018.
//

#ifndef RAW_GL_MATH_H
#define RAW_GL_MATH_H

#include <math.h>
#include "common.h"

#define PI 3.14159265359f

typedef struct vec2 {
    union {
        struct {
            float x;
            float y;
        };

        struct {
            float width;
            float height;
        };
        
        float data[2];
    };
} vec2_t;

typedef struct vec3 {
    union {
        struct {
            float x;
            float y;
            float z;
        };
        float data[3];
    };
} vec3_t;

typedef struct vec4 {
    union {
        struct {
            float x;
            float y;
            float z;
            float w;
        };
        struct {
            float r;
            float g;
            float b;
            float a;
        };
        float data[4];
    };
} vec4_t;

typedef vec4_t quat_t; 
typedef vec4_t color_t;

typedef struct mat4 {
    union {
        struct {
            vec4_t m0;
            vec4_t m1;
            vec4_t m2;
            vec4_t m3;
        };
        struct {
            vec4_t x;
            vec4_t y;
            vec4_t z;
            vec4_t w;
        };
        vec4_t data[4];
    };
} mat4_t;

typedef struct transform {
    vec3_t position;
    quat_t rotation;
    vec3_t scale;
} transform_t;

typedef struct rect {
    vec2_t position;
    vec2_t size;
} rect_t;

// ============== FLOAT

#define RAD(deg) ((deg) * PI / 180.0f)
#define DEG(rag) ((rad) * 180.0f / PI)

// ============== VEC 2

INLINE vec2_t vec2_make(float x, float y);

#define VEC2_MAKE_ONE() vec2_make(1, 1)
#define VEC2_MAKE_ZERO() vec2_make(0, 0)
#define VEC2_MAKE_UP() vec2_make(0, 1)
#define VEC2_MAKE_DOWN() vec2_make(0, -1)
#define VEC2_MAKE_RIGH() vec2_make(1, 0)
#define VEC2_MAKE_LEFT() vec2_make(-1, 0)

#define VEC2_SET_ONE(vec) vec2_set(1, 1, vec)
#define VEC2_SET_ZERO(vec) vec2_set(0, 0, vec)
#define VEC2_SET_UP(vec) vec2_set(0, 1, vec)
#define VEC2_SET_DOWN(vec) vec2_set(0, -1, vec)
#define VEC2_SET_RIGH(vec) vec2_set(1, 0, vec)
#define VEC2_SET_LEFT(vec) vec2_set(-1, 0, vec)

INLINE void vec2_set(float x, float y, vec2_t *dest);
INLINE void vec2_cpy(const vec2_t *src, vec2_t *dest);
INLINE void vec2_add(const vec2_t *a, const vec2_t *b, vec2_t *dest);
INLINE void vec2_sub(const vec2_t *a, const vec2_t *b, vec2_t *dest);
INLINE void vec2_scale(const vec2_t *a, float scalar, vec2_t *dest);
INLINE void vec2_divide(const vec2_t *a, float divider, vec2_t *dest);
INLINE void vec2_multiply(const vec2_t *a, const vec2_t *b, vec2_t *dest);
INLINE void vec2_divide_vec2(const vec2_t *a, const vec2_t *b, vec2_t *dest);
INLINE void vec2_normalize(const vec2_t *a, vec2_t *dest);
INLINE float vec2_len(const vec2_t *a);
INLINE float vec2_sqrd_len(const vec2_t *a);
INLINE float vec2_distance(const vec2_t *a, const vec2_t *b);
INLINE float vec2_sqrd_distance(const vec2_t *a, const vec2_t *b);
INLINE void vec2_max(const vec2_t *a, const vec2_t *b, vec2_t *dest);
INLINE void vec2_min(const vec2_t *a, const vec2_t *b, vec2_t *dest);
INLINE float vec2_dot(const vec2_t *a, const vec2_t *b);

// ================ VEC 3

INLINE vec3_t vec3_make(float x, float y, float z);

#define VEC3_MAKE_ONE() vec3_make(1, 1, 1)
#define VEC3_MAKE_ZERO() vec3_make(0, 0, 0)
#define VEC3_MAKE_UP() vec3_make(0, 1, 0)
#define VEC3_MAKE_DOWN() vec3_make(0, -1, 0)
#define VEC3_MAKE_FORWARD() vec3_make(0, 0, -1)
#define VEC3_MAKE_BACKWARD() vec3_make(0, 0, 1)
#define VEC3_MAKE_RIGHT() vec3_make(1, 0, 0)
#define VEC3_MAKE_LEFT() vec3_make(-1, 0, 0)

#define VEC3_SET_ONE(vec) vec3_set(1, 1, 1, vec)
#define VEC3_SET_ZERO(vec) vec3_set(0, 0, 0, vec)
#define VEC3_SET_UP(vec) vec3_set(0, 1, 0, vec)
#define VEC3_SET_DOWN(vec) vec3_set(0, -1, 0, vec)
#define VEC3_SET_FORWARD(vec) vec3_set(0, 0, -1, vec)
#define VEC3_SET_BACKWARD(vec) vec3_set(0, 0, 1, vec)
#define VEC3_SET_RIGHT(vec) vec3_set(1, 0, 0, vec)
#define VEC3_SET_LEFT(vec) vec3_set(-1, 0, 0, vec)

INLINE void vec3_set(float x, float y, float z, vec3_t *dest);
INLINE void vec3_cpy(const vec3_t *src, vec3_t *dest);
INLINE void vec3_add(const vec3_t *a, const vec3_t *b, vec3_t *dest);
INLINE void vec3_sub(const vec3_t *a, const vec3_t *b, vec3_t *dest);
INLINE void vec3_scale_vec3(const vec3_t *a, const vec3_t *b, vec3_t *dest);
INLINE void vec3_scale(const vec3_t *a, float scalar, vec3_t *dest);
INLINE void vec3_divide(const vec3_t *a, float divider, vec3_t *dest);
INLINE void vec3_multiply(const vec3_t *a, const vec3_t *b, vec3_t *dest);
INLINE void vec3_divide_vec3(const vec3_t *a, const vec3_t *b, vec3_t *dest);
INLINE void vec3_normalize(const vec3_t *a, vec3_t *dest);
INLINE float vec3_len(const vec3_t *a);
INLINE float vec3_sqrd_len(const vec3_t *a);
INLINE float vec3_distance(const vec3_t *a, const vec3_t *b);
INLINE float vec3_sqrd_distance(const vec3_t *a, const vec3_t *b);
INLINE void vec3_rotate(const vec3_t *v, float angle, const vec3_t *axis, vec3_t *dest);
INLINE void vec3_max(const vec3_t *a, const vec3_t *b, vec3_t *dest);
INLINE void vec3_min(const vec3_t *a, const vec3_t *b, vec3_t *dest);
INLINE void vec3_ortho(const vec3_t *a, vec3_t *dest);
INLINE float vec3_dot(const vec3_t *a, const vec3_t *b);
INLINE void vec3_cross(const vec3_t *a, const vec3_t *b, vec3_t *dest);
INLINE float vec3_angle(const vec3_t *a, const vec3_t *b);
INLINE float vec3_inv(const vec3_t *a, vec3_t *dest);
INLINE void vec3_lerp(const vec3_t *a, const vec3_t *b, float t, vec3_t *dest);

// ================ VEC 4

INLINE vec4_t vec4_make(float x, float y, float z, float w);
INLINE void vec4_set(float x, float y, float z, float w, vec4_t *dest);
INLINE void vec4_cpy(const vec4_t *src, vec4_t *dest);
INLINE void vec4_add(const vec4_t *a, const vec4_t *b, vec4_t *dest);
INLINE void vec4_sub(const vec4_t *a, const vec4_t *b, vec4_t *dest);
INLINE void vec4_scale(const vec4_t *a, float scalar, vec4_t *dest);
INLINE void vec4_divide(const vec4_t *a, float divider, vec4_t *dest);
INLINE void vec4_multiply(const vec4_t *a, const vec4_t *b, vec4_t *dest);
INLINE void vec4_divide_vec4(const vec4_t *a, const vec4_t *b, vec4_t *dest);
INLINE void vec4_normalize(const vec4_t *a, vec4_t *dest);
INLINE float vec4_len(const vec4_t *a);
INLINE float vec4_sqrd_len(const vec4_t *a);
INLINE float vec4_distance(const vec4_t *a, const vec4_t *b);
INLINE float vec4_sqrd_distance(const vec4_t *a, const vec4_t *b);
INLINE void vec4_max(const vec4_t *a, const vec4_t *b, vec4_t *dest);
INLINE void vec4_min(const vec4_t *a, const vec4_t *b, vec4_t *dest);
INLINE float vec4_dot(const vec4_t *a, const vec4_t *b);
INLINE float vec4_inv(const vec4_t *a, vec4_t *dest);
INLINE void vec4_lerp(const vec4_t *a, const vec4_t *b, float t, vec4_t *dest);

// ================ QUAT

#define QUAT_MAKE_IDENTITY() vec4_make(0, 0, 0, 1)
INLINE void quat_identity(quat_t *dest);
INLINE void quat_angle_axis(const vec3_t *axis, float angle, quat_t *dest);
INLINE void quat_conjugate(const quat_t *a, quat_t *dest);
INLINE void quat_multiply(const quat_t *a, const quat_t *b, quat_t *dest);
INLINE void quat_to_mat4(const quat_t *a, mat4_t *dest);
INLINE void quat_to_mat4_transposed(const quat_t *a, mat4_t *dest);
INLINE void quat_lerp(const quat_t *a, const quat_t *b, float t, quat_t *dest);
INLINE void quat_slerp(const quat_t *a, const quat_t *b, float t, quat_t *dest);
INLINE void quat_look_to_mat(const vec3_t *position, const quat_t *rotation, mat4_t *dest);
INLINE void quat_rotate_matrix(const mat4_t *mat, const quat_t *rotation, mat4_t *dest);
INLINE void quat_rotate_vec3(const vec3_t *v, const quat_t *rotation, vec3_t *dest);
INLINE void quat_look_rotation(const vec3_t *dir, const vec3_t *forward, const vec3_t *up, quat_t *dest);
INLINE void quat_look_from_to(const vec3_t *from, const vec3_t *to, const vec3_t *forward, const vec3_t *up, quat_t *dest);
INLINE void quat_normalize(const quat_t *a, quat_t *dest);

// ================= COLOR

#define COLOR_MAKE_WHITE() vec4_make(1, 1, 1, 1)
#define COLOR_MAKE_BLACK() vec4_make(0, 0, 0, 1)
#define COLOR_MAKE_RED() vec4_make(1, 0, 0, 1)
#define COLOR_MAKE_GREEN() vec4_make(1, 0, 0, 1)
#define COLOR_MAKE_BLUE() vec4_make(1, 0, 0, 1)
#define COLOR_MAKE_YELLOW() vec4_make(1, 1, 0, 1)
#define COLOR_MAKE_MAGENTA() vec4_make(1, 0, 1, 1)
#define COLOR_MAKE_CYAN() vec4_make(0, 1, 1, 1)

#define COLOR_SET_WHITE(vec) vec4_set(1, 1, 1, 1, vec)
#define COLOR_SET_BLACK(vec) vec4_set(0, 0, 0, 1, vec)
#define COLOR_SET_RED(vec) vec4_set(1, 0, 0, 1, vec)
#define COLOR_SET_GREEN(vec) vec4_set(0, 1, 0, 1, vec)
#define COLOR_SET_BLUE(vec) vec4_set(0, 0, 1, 1, vec)
#define COLOR_SET_YELLOW(vec) vec4_set(1, 1, 0, 1, vec)
#define COLOR_SET_MAGENTA(vec) vec4_set(1, 0, 1, 1, vec)
#define COLOR_SET_CYAN(vec) vec4_set(0, 1, 1, 1, vec)

// ================= MAT4

INLINE mat4_t mat4_make_identity();
INLINE void mat4_identity(mat4_t *dest);
INLINE mat4_t mat4_make(vec4_t x, vec4_t y, vec4_t z, vec4_t w);
INLINE void mat4_set(vec4_t x, vec4_t y, vec4_t z, vec4_t w, mat4_t *dest);
INLINE void mat4_cpy(const mat4_t *mat, mat4_t *dest);
INLINE void mat4_mul(const mat4_t *a, const mat4_t *b, mat4_t *dest);
INLINE void mat4_to_quat(const mat4_t *mat, quat_t *dest);
INLINE void mat4_mul_vec4(const mat4_t *mat, const vec4_t *vec, vec4_t *dest);
INLINE void mat4_mul_vec3(const mat4_t *mat, const vec3_t *vec, vec3_t *dest);
INLINE void mat4_transpose(const mat4_t *mat, mat4_t *dest);
INLINE void mat4_mul_scalar(const mat4_t *mat, float scalar, mat4_t *dest);
INLINE float mat4_det(const mat4_t *mat);
INLINE void mat4_inv(const mat4_t *mat, mat4_t *dest);
INLINE void mat4_frustum(float left, float right, float bottom, float top, float near_plane, float far_plane, mat4_t *dest);
INLINE void mat4_ortho(float left, float right, float bottom, float top, float near_plane, float far_plane, mat4_t *dest);
INLINE void mat4_perspective(float field_of_view, float aspect, float near_plane, float far_plane, mat4_t *dest);
INLINE void mat4_look_at(const vec3_t *pos, const vec3_t *center, const vec3_t *up, mat4_t *dest);
INLINE void mat4_look(const vec3_t *pos, const vec3_t *dir, const vec3_t *up, mat4_t *dest);
INLINE void mat4_decompose_perspective(const mat4_t *proj, float *near_plane, float *far_plane, float *top, float *bottom, float *left, float *right);
INLINE void mat4_set_translate(const vec3_t *position, mat4_t *dest);
INLINE void mat4_set_scale(const vec3_t *scale, mat4_t *dest);
INLINE void mat4_set_rotate(const quat_t *rotation, mat4_t *dest);
INLINE void mat4_translate(const mat4_t *mat, const vec3_t *position, mat4_t *dest);
INLINE void mat4_scale(const mat4_t *mat, const vec3_t *scale, mat4_t *dest);
INLINE void mat4_rotate(const mat4_t *mat, const quat_t *rotation, mat4_t *dest);

// ================== TRANSFORM

// TODO(temdisponivel): Make easier functions for this (not using pointers)
INLINE transform_t trans_make(const vec3_t *pos, const vec3_t *scale, const quat_t *rotation);
INLINE void trans_set(const vec3_t *pos, const vec3_t *scale, const quat_t *rotation, transform_t *dest);
INLINE void trans_get_mat4(const transform_t *trans, mat4_t *dest);
INLINE void trans_get_forward(const transform_t *trans, vec3_t *dest);
INLINE void trans_get_up(const transform_t *trans, vec3_t *dest);
INLINE void trans_get_right(const transform_t *trans, vec3_t *dest);
INLINE void trans_get_backward(const transform_t *trans, vec3_t *dest);
INLINE void trans_get_down(const transform_t *trans, vec3_t *dest);
INLINE void trans_get_left(const transform_t *trans, vec3_t *dest);

// ======================= RECT

INLINE rect_t rect_make(const vec2_t *position, const vec2_t *size);
INLINE void rect_set(const vec2_t *position, const vec2_t *size, rect_t *rect);

#include "vec2.iln"
#include "vec3.iln"
#include "vec4.iln"
#include "mat4.iln"
#include "quat.iln"
#include "transform.iln"
#include "rect.iln"

#define PRINT_VEC2(vec) printf("x: %f y: %f\n", vec.x, vec.y)
#define PRINT_VEC3(vec) printf("x: %f y: %f z: %f\n", vec.x, vec.y, vec.z)
#define PRINT_VEC4(vec) printf("x: %f y: %f z: %f w: %f\n ", vec.x, vec.y, vec.z, vec.w)

// TODO(temdisponivel): Make functions to print these data types!!!

#endif //RAW_GL_MATH_H
