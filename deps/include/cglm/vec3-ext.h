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
   CGLM_INLINE void  glm_vec_mulv(vec3 a, vec3 b, vec3 d);
   CGLM_INLINE void  glm_vec_broadcast(float val, vec3 d);
   CGLM_INLINE bool  glm_vec_eq(vec3 v, float val);
   CGLM_INLINE bool  glm_vec_eq_eps(vec3 v, float val);
   CGLM_INLINE bool  glm_vec_eq_all(vec3 v);
   CGLM_INLINE bool  glm_vec_eqv(vec3 v1, vec3 v2);
   CGLM_INLINE bool  glm_vec_eqv_eps(vec3 v1, vec3 v2);
   CGLM_INLINE float glm_vec_max(vec3 v);
   CGLM_INLINE float glm_vec_min(vec3 v);
 */

#ifndef cglm_vec3_ext_h
#define cglm_vec3_ext_h

#include "common.h"
#include "util.h"
#include <stdbool.h>
#include <math.h>
#include <float.h>

/*!
 * @brief DEPRECATED! use glm_vec_mul
 *
 * @param[in]  a vec1
 * @param[in]  b vec2
 * @param[out] d vec3 = (v1.data[0] * v2.data[0],  v1.data[1] * v2.data[1], v1.data[2] * v2.data[2])
 */
CGLM_INLINE
void
glm_vec_mulv(vec3 a, vec3 b, vec3 d) {
  d.data[0] = a.data[0] * b.data[0];
  d.data[1] = a.data[1] * b.data[1];
  d.data[2] = a.data[2] * b.data[2];
}

/*!
 * @brief fill a vector with specified value
 *
 * @param[in]  val value
 * @param[out] d   dest
 */
CGLM_INLINE
void
glm_vec_broadcast(float val, vec3 d) {
  d.data[0] = d.data[1] = d.data[2] = val;
}

/*!
 * @brief check if vector is equal to value (without epsilon)
 *
 * @param[in] v   vector
 * @param[in] val value
 */
CGLM_INLINE
bool
glm_vec_eq(vec3 v, float val) {
  return v.data[0] == val && v.data[0] == v.data[1] && v.data[0] == v.data[2];
}

/*!
 * @brief check if vector is equal to value (with epsilon)
 *
 * @param[in] v   vector
 * @param[in] val value
 */
CGLM_INLINE
bool
glm_vec_eq_eps(vec3 v, float val) {
  return fabsf(v.data[0] - val) <= FLT_EPSILON
         && fabsf(v.data[1] - val) <= FLT_EPSILON
         && fabsf(v.data[2] - val) <= FLT_EPSILON;
}

/*!
 * @brief check if vectors members are equal (without epsilon)
 *
 * @param[in] v   vector
 */
CGLM_INLINE
bool
glm_vec_eq_all(vec3 v) {
  return v.data[0] == v.data[1] && v.data[0] == v.data[2];
}

/*!
 * @brief check if vector is equal to another (without epsilon)
 *
 * @param[in] v1 vector
 * @param[in] v2 vector
 */
CGLM_INLINE
bool
glm_vec_eqv(vec3 v1, vec3 v2) {
  return v1.data[0] == v2.data[0]
        && v1.data[1] == v2.data[1]
        && v1.data[2] == v2.data[2];
}

/*!
 * @brief check if vector is equal to another (with epsilon)
 *
 * @param[in] v1 vector
 * @param[in] v2 vector
 */
CGLM_INLINE
bool
glm_vec_eqv_eps(vec3 v1, vec3 v2) {
  return fabsf(v1.data[0] - v2.data[0]) <= FLT_EPSILON
         && fabsf(v1.data[1] - v2.data[1]) <= FLT_EPSILON
         && fabsf(v1.data[2] - v2.data[2]) <= FLT_EPSILON;
}

/*!
 * @brief max value of vector
 *
 * @param[in] v vector
 */
CGLM_INLINE
float
glm_vec_max(vec3 v) {
  float max;

  max = v.data[0];
  if (v.data[1] > max)
    max = v.data[1];
  if (v.data[2] > max)
    max = v.data[2];

  return max;
}

/*!
 * @brief min value of vector
 *
 * @param[in] v vector
 */
CGLM_INLINE
float
glm_vec_min(vec3 v) {
  float min;

  min = v.data[0];
  if (v.data[1] < min)
    min = v.data[1];
  if (v.data[2] < min)
    min = v.data[2];

  return min;
}

/*!
 * @brief check if all items are NaN (not a number)
 *        you should only use this in DEBUG mode or very critical asserts
 *
 * @param[in] v vector
 */
CGLM_INLINE
bool
glm_vec_isnan(vec3 v) {
  return isnan(v.data[0]) || isnan(v.data[1]) || isnan(v.data[2]);
}

/*!
 * @brief check if all items are INFINITY
 *        you should only use this in DEBUG mode or very critical asserts
 *
 * @param[in] v vector
 */
CGLM_INLINE
bool
glm_vec_isinf(vec3 v) {
  return isinf(v.data[0]) || isinf(v.data[1]) || isinf(v.data[2]);
}

/*!
 * @brief check if all items are valid number
 *        you should only use this in DEBUG mode or very critical asserts
 *
 * @param[in] v vector
 */
CGLM_INLINE
bool
glm_vec_isvalid(vec3 v) {
  return !glm_vec_isnan(v) && !glm_vec_isinf(v);
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
glm_vec_sign(vec3 v, vec3 dest) {
  dest.data[0] = glm_signf(v.data[0]);
  dest.data[1] = glm_signf(v.data[1]);
  dest.data[2] = glm_signf(v.data[2]);
}

/*!
 * @brief square root of each vector item
 *
 * @param[in]  v    vector
 * @param[out] dest destination vector
 */
CGLM_INLINE
void
glm_vec_sqrt(vec3 v, vec3 dest) {
  dest.data[0] = sqrtf(v.data[0]);
  dest.data[1] = sqrtf(v.data[1]);
  dest.data[2] = sqrtf(v.data[2]);
}

#endif /* cglm_vec3_ext_h */
