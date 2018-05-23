/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

/*!
 * @brief SIMD like functions
 */

/*
 Functions:
   CGLM_INLINE void  glm_vec4_mulv(vec4 a, vec4 b, vec4 d);
   CGLM_INLINE void  glm_vec4_broadcast(float val, vec4 d);
   CGLM_INLINE bool  glm_vec4_eq(vec4 v, float val);
   CGLM_INLINE bool  glm_vec4_eq_eps(vec4 v, float val);
   CGLM_INLINE bool  glm_vec4_eq_all(vec4 v);
   CGLM_INLINE bool  glm_vec4_eqv(vec4 v1, vec4 v2);
   CGLM_INLINE bool  glm_vec4_eqv_eps(vec4 v1, vec4 v2);
   CGLM_INLINE float glm_vec4_max(vec4 v);
   CGLM_INLINE float glm_vec4_min(vec4 v);
 */

#ifndef cglm_vec4_ext_h
#define cglm_vec4_ext_h

#include "common.h"
#include "vec3-ext.h"
#include <stdbool.h>
#include <math.h>
#include <float.h>

/*!
 * @brief DEPRECATED! use glm_vec4_mul
 *
 * @param a v1
 * @param b v2
 * @param d v3 = (v1.data[0] * v2.data[0],  v1.data[1] * v2.data[1], v1.data[2] * v2.data[2], v1.data[3] * v2.data[3])
 */
CGLM_INLINE
void
glm_vec4_mulv(vec4 a, vec4 b, vec4 d) {
#if defined( __SSE__ ) || defined( __SSE2__ )
  glmm_store(d, _mm_mul_ps(glmm_load(a), glmm_load(b)));
#else
  d.data[0] = a.data[0] * b.data[0];
  d.data[1] = a.data[1] * b.data[1];
  d.data[2] = a.data[2] * b.data[2];
  d.data[3] = a.data[3] * b.data[3];
#endif
}

/*!
 * @brief fill a vector with specified value
 *
 * @param val value
 * @param d   dest
 */
CGLM_INLINE
void
glm_vec4_broadcast(float val, vec4 d) {
#if defined( __SSE__ ) || defined( __SSE2__ )
  glmm_store(d, _mm_set1_ps(val));
#else
  d.data[0] = d.data[1] = d.data[2] = d.data[3] = val;
#endif
}

/*!
 * @brief check if vector is equal to value (without epsilon)
 *
 * @param v   vector
 * @param val value
 */
CGLM_INLINE
bool
glm_vec4_eq(vec4 v, float val) {
  return v.data[0] == val
         && v.data[0] == v.data[1]
         && v.data[0] == v.data[2]
         && v.data[0] == v.data[3];
}

/*!
 * @brief check if vector is equal to value (with epsilon)
 *
 * @param v   vector
 * @param val value
 */
CGLM_INLINE
bool
glm_vec4_eq_eps(vec4 v, float val) {
  return fabsf(v.data[0] - val) <= FLT_EPSILON
         && fabsf(v.data[1] - val) <= FLT_EPSILON
         && fabsf(v.data[2] - val) <= FLT_EPSILON
         && fabsf(v.data[3] - val) <= FLT_EPSILON;
}

/*!
 * @brief check if vectors members are equal (without epsilon)
 *
 * @param v   vector
 */
CGLM_INLINE
bool
glm_vec4_eq_all(vec4 v) {
  return v.data[0] == v.data[1]
         && v.data[0] == v.data[2]
         && v.data[0] == v.data[3];
}

/*!
 * @brief check if vector is equal to another (without epsilon)
 *
 * @param v1 vector
 * @param v2 vector
 */
CGLM_INLINE
bool
glm_vec4_eqv(vec4 v1, vec4 v2) {
  return v1.data[0] == v2.data[0]
         && v1.data[1] == v2.data[1]
         && v1.data[2] == v2.data[2]
         && v1.data[3] == v2.data[3];
}

/*!
 * @brief check if vector is equal to another (with epsilon)
 *
 * @param v1 vector
 * @param v2 vector
 */
CGLM_INLINE
bool
glm_vec4_eqv_eps(vec4 v1, vec4 v2) {
  return fabsf(v1.data[0] - v2.data[0]) <= FLT_EPSILON
         && fabsf(v1.data[1] - v2.data[1]) <= FLT_EPSILON
         && fabsf(v1.data[2] - v2.data[2]) <= FLT_EPSILON
         && fabsf(v1.data[3] - v2.data[3]) <= FLT_EPSILON;
}

/*!
 * @brief max value of vector
 *
 * @param v vector
 */
CGLM_INLINE
float
glm_vec4_max(vec4 v) {
  float max;

  max = v.data[0];
  if (v.data[1] > max)
    max = v.data[1];
  if (v.data[2] > max)
    max = v.data[2];
  if (v.data[3] > max)
    max = v.data[3];

  return max;
}

/*!
 * @brief min value of vector
 *
 * @param v vector
 */
CGLM_INLINE
float
glm_vec4_min(vec4 v) {
  float min;

  min = v.data[0];
  if (v.data[1] < min)
    min = v.data[1];
  if (v.data[2] < min)
    min = v.data[2];
  if (v.data[3] < min)
    min = v.data[3];

  return min;
}

/*!
 * @brief check if one of items is NaN (not a number)
 *        you should only use this in DEBUG mode or very critical asserts
 *
 * @param[in] v vector
 */
CGLM_INLINE
bool
glm_vec4_isnan(vec4 v) {
  return isnan(v.data[0]) || isnan(v.data[1]) || isnan(v.data[2]) || isnan(v.data[3]);
}

/*!
 * @brief check if one of items is INFINITY
 *        you should only use this in DEBUG mode or very critical asserts
 *
 * @param[in] v vector
 */
CGLM_INLINE
bool
glm_vec4_isinf(vec4 v) {
  return isinf(v.data[0]) || isinf(v.data[1]) || isinf(v.data[2]) || isinf(v.data[3]);
}

/*!
 * @brief check if all items are valid number
 *        you should only use this in DEBUG mode or very critical asserts
 *
 * @param[in] v vector
 */
CGLM_INLINE
bool
glm_vec4_isvalid(vec4 v) {
  return !glm_vec4_isnan(v) && !glm_vec4_isinf(v);
}

/*!
 * @brief get sign of 32 bit float as +1, -1, 0
 *
 * Important: It returns 0 for zero/NaN input
 *
 * @param v vector
 */
CGLM_INLINE
void
glm_vec4_sign(vec4 v, vec4 dest) {
#if defined( __SSE2__ ) || defined( __SSE2__ )
  __m128 x0, x1, x2, x3, x4;

  x0 = glmm_load(v);
  x1 = _mm_set_ps(0.0f, 0.0f, 1.0f, -1.0f);
  x2 = glmm_shuff1x(x1, 2);

  x3 = _mm_and_ps(_mm_cmpgt_ps(x0, x2), glmm_shuff1x(x1, 1));
  x4 = _mm_and_ps(_mm_cmplt_ps(x0, x2), glmm_shuff1x(x1, 0));

  glmm_store(dest, _mm_or_ps(x3, x4));
#else
  dest.data[0] = glm_signf(v.data[0]);
  dest.data[1] = glm_signf(v.data[1]);
  dest.data[2] = glm_signf(v.data[2]);
  dest.data[3] = glm_signf(v.data[3]);
#endif
}

/*!
 * @brief square root of each vector item
 *
 * @param[in]  v    vector
 * @param[out] dest destination vector
 */
CGLM_INLINE
void
glm_vec4_sqrt(vec4 v, vec4 dest) {
#if defined( __SSE__ ) || defined( __SSE2__ )
  glmm_store(dest, _mm_sqrt_ps(glmm_load(v)));
#else
  dest.data[0] = sqrtf(v.data[0]);
  dest.data[1] = sqrtf(v.data[1]);
  dest.data[2] = sqrtf(v.data[2]);
  dest.data[3] = sqrtf(v.data[3]);
#endif
}

#endif /* cglm_vec4_ext_h */
