/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

/*
 Functions:
   CGLM_INLINE void  glm_frustum(float left,
                                 float right,
                                 float bottom,
                                 float top,
                                 float nearVal,
                                 float farVal,
                                 mat4  dest)
   CGLM_INLINE void  glm_ortho(float left,
                               float right,
                               float bottom,
                               float top,
                               float nearVal,
                               float farVal,
                               mat4  dest)
   CGLM_INLINE void  glm_ortho_aabb(vec3 box[2], mat4 dest)
   CGLM_INLINE void  glm_ortho_aabb_p(vec3 box[2], float padding, mat4 dest)
   CGLM_INLINE void  glm_ortho_aabb_pz(vec3 box[2], float padding, mat4 dest)
   CGLM_INLINE void  glm_ortho_default(float aspect, mat4  dest)
   CGLM_INLINE void  glm_ortho_default_s(float aspect, float size, mat4  dest)
   CGLM_INLINE void  glm_perspective(float fovy,
                                     float aspect,
                                     float nearVal,
                                     float farVal,
                                     mat4  dest)
   CGLM_INLINE void  glm_perspective_default(float aspect, mat4  dest)
   CGLM_INLINE void  glm_perspective_resize(float aspect, mat4  proj)
   CGLM_INLINE void  glm_lookat(vec3 eye, vec3 center, vec3 up, mat4 dest)
   CGLM_INLINE void  glm_look(vec3 eye, vec3 dir, vec3 up, mat4 dest)
   CGLM_INLINE void  glm_look_anyup(vec3 eye, vec3 dir, mat4 dest)
   CGLM_INLINE void  glm_persp_decomp(mat4   proj,
                                      float *nearVal,
                                      float *farVal,
                                      float *top,
                                      float *bottom,
                                      float *left,
                                      float *right)
   CGLM_INLINE void  glm_persp_decompv(mat4 proj, float dest[6])
   CGLM_INLINE void  glm_persp_decomp_x(mat4 proj, float *left, float *right)
   CGLM_INLINE void  glm_persp_decomp_y(mat4 proj, float *top,  float *bottom)
   CGLM_INLINE void  glm_persp_decomp_z(mat4 proj,
                                        float *nearVal,
                                        float *farVal)
   CGLM_INLINE void  glm_persp_decomp_far(mat4 proj, float *farVal)
   CGLM_INLINE void  glm_persp_decomp_near(mat4 proj, float *nearVal)
   CGLM_INLINE float glm_persp_fovy(mat4 proj)
   CGLM_INLINE float glm_persp_aspect(mat4 proj)
   CGLM_INLINE void  glm_persp_sizes(mat4 proj, float fovy, vec4 dest)
 */

#ifndef cglm_vcam_h
#define cglm_vcam_h

#include "common.h"
#include "plane.h"

/*!
 * @brief set up perspective peprojection matrix
 *
 * @param[in]  left    viewport.left
 * @param[in]  right   viewport.right
 * @param[in]  bottom  viewport.bottom
 * @param[in]  top     viewport.top
 * @param[in]  nearVal near clipping plane
 * @param[in]  farVal  far clipping plane
 * @param[out] dest    result matrix
 */
CGLM_INLINE
void
glm_frustum(float left,
            float right,
            float bottom,
            float top,
            float nearVal,
            float farVal,
            mat4  dest) {
  float rl, tb, fn, nv;

  glm__memzero(float, dest, sizeof(mat4));

  rl = 1.0f / (right  - left);
  tb = 1.0f / (top    - bottom);
  fn =-1.0f / (farVal - nearVal);
  nv = 2.0f * nearVal;

  dest->data[0].data[0] = nv * rl;
  dest->data[1].data[1] = nv * tb;
  dest->data[2].data[0] = (right  + left)    * rl;
  dest->data[2].data[1] = (top    + bottom)  * tb;
  dest->data[2].data[2] = (farVal + nearVal) * fn;
  dest->data[2].data[3] =-1.0f;
  dest->data[3].data[2] = farVal * nv * fn;
}

/*!
 * @brief set up orthographic projection matrix
 *
 * @param[in]  left    viewport.left
 * @param[in]  right   viewport.right
 * @param[in]  bottom  viewport.bottom
 * @param[in]  top     viewport.top
 * @param[in]  nearVal near clipping plane
 * @param[in]  farVal  far clipping plane
 * @param[out] dest    result matrix
 */
CGLM_INLINE
void
glm_ortho(float left,
          float right,
          float bottom,
          float top,
          float nearVal,
          float farVal,
          mat4  dest) {
  float rl, tb, fn;

  glm__memzero(float, dest, sizeof(mat4));

  rl = 1.0f / (right  - left);
  tb = 1.0f / (top    - bottom);
  fn =-1.0f / (farVal - nearVal);

  dest->data[0].data[0] = 2.0f * rl;
  dest->data[1].data[1] = 2.0f * tb;
  dest->data[2].data[2] = 2.0f * fn;
  dest->data[3].data[0] =-(right  + left)    * rl;
  dest->data[3].data[1] =-(top    + bottom)  * tb;
  dest->data[3].data[2] = (farVal + nearVal) * fn;
  dest->data[3].data[3] = 1.0f;
}
/*

*/
/*!
 * @brief set up orthographic projection matrix using bounding box
 *
 * bounding box (AABB) must be in view space
 *
 * @param[in]  box   AABB
 * @param[out] dest  result matrix
 *//*

CGLM_INLINE
void
glm_ortho_aabb(vec3 box[2], mat4 dest) {
  glm_ortho(box[0]->data[0],  box[1]->data[0],
            box[0]->data[1],  box[1]->data[1],
           -box[1]->data[2], -box[0]->data[2],
            dest);
}

*/
/*!
 * @brief set up orthographic projection matrix using bounding box
 *
 * bounding box (AABB) must be in view space
 *
 * @param[in]  box     AABB
 * @param[in]  padding padding
 * @param[out] dest    result matrix
 *//*

CGLM_INLINE
void
glm_ortho_aabb_p(vec3 box[2], float padding, mat4 dest) {
  glm_ortho(box[0]->data[0] - padding,    box[1]->data[0] + padding,
            box[0]->data[1] - padding,    box[1]->data[1] + padding,
          -(box[1]->data[2] + padding), -(box[0]->data[2] - padding),
            dest);
}

*/
/*!
 * @brief set up orthographic projection matrix using bounding box
 *
 * bounding box (AABB) must be in view space
 *
 * @param[in]  box     AABB
 * @param[in]  padding padding for near and far
 * @param[out] dest    result matrix
 *//*

CGLM_INLINE
void
glm_ortho_aabb_pz(vec3 box[2], float padding, mat4 dest) {
  glm_ortho(box[0]->data[0],              box[1]->data[0],
            box[0]->data[1],              box[1]->data[1],
          -(box[1]->data[2] + padding), -(box[0]->data[2] - padding),
            dest);
}
*/

/*!
 * @brief set up unit orthographic projection matrix
 *
 * @param[in]  aspect aspect ration ( width / height )
 * @param[out] dest   result matrix
 */
CGLM_INLINE
void
glm_ortho_default(float aspect,
                  mat4  dest) {
  if (aspect >= 1.0f) {
    glm_ortho(-1.0f * aspect,
               1.0f * aspect,
              -1.0f,
               1.0f,
              -100.0f,
               100.0f,
               dest);
	  return;
  }

  glm_ortho(-1.0f,
             1.0f,
            -1.0f / aspect,
             1.0f / aspect,
            -100.0f,
             100.0f,
             dest);
}

/*!
 * @brief set up orthographic projection matrix with given CUBE size
 *
 * @param[in]  aspect aspect ratio ( width / height )
 * @param[in]  size   cube size
 * @param[out] dest   result matrix
 */
CGLM_INLINE
void
glm_ortho_default_s(float aspect,
                    float size,
                    mat4  dest) {
  if (aspect >= 1.0f) {
    glm_ortho(-size * aspect,
               size * aspect,
              -size,
               size,
              -size - 100.0f,
               size + 100.0f,
               dest);
	  return;
  }

  glm_ortho(-size,
             size,
            -size / aspect,
             size / aspect,
            -size - 100.0f,
             size + 100.0f,
             dest);
}

/*!
 * @brief set up perspective projection matrix
 *
 * @param[in]  fovy    field of view angle
 * @param[in]  aspect  aspect ratio ( width / height )
 * @param[in]  nearVal near clipping plane
 * @param[in]  farVal  far clipping planes
 * @param[out] dest    result matrix
 */
CGLM_INLINE
void
glm_perspective(float fovy,
                float aspect,
                float nearVal,
                float farVal,
                mat4  dest) {
  float f, fn;

  glm__memzero(float, dest, sizeof(mat4));

  f  = 1.0f / tanf(fovy * 0.5f);
  fn = 1.0f / (nearVal - farVal);

  dest->data[0].data[0] = f / aspect;
  dest->data[1].data[1] = f;
  dest->data[2].data[2] = (nearVal + farVal) * fn;
  dest->data[2].data[3] =-1.0f;
  dest->data[3].data[2] = 2.0f * nearVal * farVal * fn;
}

/*!
 * @brief set up perspective projection matrix with default near/far
 *        and angle values
 *
 * @param[in]  aspect aspect ratio ( width / height )
 * @param[out] dest   result matrix
 */
CGLM_INLINE
void
glm_perspective_default(float aspect,
                        mat4  dest) {
  glm_perspective((float)CGLM_PI_4,
                  aspect,
                  0.01f,
                  100.0f,
                  dest);
}

/*!
 * @brief resize perspective matrix by aspect ratio ( width / height )
 *        this makes very easy to resize proj matrix when window /viewport
 *        reized
 *
 * @param[in]      aspect aspect ratio ( width / height )
 * @param[in, out] proj   perspective projection matrix
 */
CGLM_INLINE
void
glm_perspective_resize(float aspect,
                       mat4  proj) {
  if (proj->data[0].data[0] == 0.0f)
    return;

  proj->data[0].data[0] = proj->data[1].data[1] / aspect;
}

/*!
 * @brief set up view matrix
 *
 * @param[in]  eye    eye vector
 * @param[in]  center center vector
 * @param[in]  up     up vector
 * @param[out] dest   result matrix
 */
CGLM_INLINE
void
glm_lookat(vec3 eye,
           vec3 center,
           vec3 up,
           mat4 dest) {
  vec3 f, u, s;

  glm_vec_sub(center, eye, f);
  glm_vec_normalize(f);

  glm_vec_cross(f, up, s);
  glm_vec_normalize(s);

  glm_vec_cross(s, f, u);

  dest->data[0].data[0] = s->data[0];
  dest->data[0].data[1] = u->data[0];
  dest->data[0].data[2] =-f->data[0];
  dest->data[1].data[0] = s->data[1];
  dest->data[1].data[1] = u->data[1];
  dest->data[1].data[2] =-f->data[1];
  dest->data[2].data[0] = s->data[2];
  dest->data[2].data[1] = u->data[2];
  dest->data[2].data[2] =-f->data[2];
  dest->data[3].data[0] =-glm_vec_dot(s, eye);
  dest->data[3].data[1] =-glm_vec_dot(u, eye);
  dest->data[3].data[2] = glm_vec_dot(f, eye);
  dest->data[0].data[3] = dest->data[1].data[3] = dest->data[2].data[3] = 0.0f;
  dest->data[3].data[3] = 1.0f;
}

/*!
 * @brief set up view matrix
 *
 * convenient wrapper for lookat: if you only have direction not target self
 * then this might be useful. Because you need to get target from direction.
 *
 * @param[in]  eye    eye vector
 * @param[in]  dir    direction vector
 * @param[in]  up     up vector
 * @param[out] dest   result matrix
 */
CGLM_INLINE
void
glm_look(vec3 eye, vec3 dir, vec3 up, mat4 dest) {
  vec3 target;
  glm_vec_add(eye, dir, target);
  glm_lookat(eye, target, up, dest);
}

/*!
 * @brief set up view matrix
 *
 * convenient wrapper for look: if you only have direction and if you don't
 * care what UP vector is then this might be useful to create view matrix
 *
 * @param[in]  eye    eye vector
 * @param[in]  dir    direction vector
 * @param[out] dest   result matrix
 */
CGLM_INLINE
void
glm_look_anyup(vec3 eye, vec3 dir, mat4 dest) {
  vec3 up;
  glm_vec_ortho(dir, up);
  glm_look(eye, dir, up, dest);
}

/*!
 * @brief decomposes frustum values of perspective projection.
 *
 * @param[in]  proj    perspective projection matrix
 * @param[out] nearVal near
 * @param[out] farVal  far
 * @param[out] top     top
 * @param[out] bottom  bottom
 * @param[out] left    left
 * @param[out] right   right
 */
CGLM_INLINE
void
glm_persp_decomp(mat4 proj,
                 float * __restrict nearVal,
                 float * __restrict farVal,
                 float * __restrict top,
                 float * __restrict bottom,
                 float * __restrict left,
                 float * __restrict right) {
  float m00, m11, m20, m21, m22, m32, n, f;
  float n_m11, n_m00;

  m00 = proj->data[0].data[0];
  m11 = proj->data[1].data[1];
  m20 = proj->data[2].data[0];
  m21 = proj->data[2].data[1];
  m22 = proj->data[2].data[2];
  m32 = proj->data[3].data[2];

  n = m32 / (m22 - 1.0f);
  f = m32 / (m22 + 1.0f);

  n_m11 = n / m11;
  n_m00 = n / m00;

  *nearVal = n;
  *farVal  = f;
  *bottom  = n_m11 * (m21 - 1.0f);
  *top     = n_m11 * (m21 + 1.0f);
  *left    = n_m00 * (m20 - 1.0f);
  *right   = n_m00 * (m20 + 1.0f);
}

/*!
 * @brief decomposes frustum values of perspective projection.
 *        this makes easy to get all values at once
 *
 * @param[in]  proj   perspective projection matrix
 * @param[out] dest   array
 */
CGLM_INLINE
void
glm_persp_decompv(mat4 proj, float dest[6]) {
  glm_persp_decomp(proj, &dest[0], &dest[1], &dest[2],
                         &dest[3], &dest[4], &dest[5]);
}

/*!
 * @brief decomposes left and right values of perspective projection.
 *        x stands for x axis (left / right axis)
 *
 * @param[in]  proj  perspective projection matrix
 * @param[out] left  left
 * @param[out] right right
 */
CGLM_INLINE
void
glm_persp_decomp_x(mat4 proj,
                   float * __restrict left,
                   float * __restrict right) {
  float nearVal, m20, m00;

  m00 = proj->data[0].data[0];
  m20 = proj->data[2].data[0];

  nearVal = proj->data[3].data[2] / (proj->data[3].data[3] - 1.0f);
  *left   = nearVal * (m20 - 1.0f) / m00;
  *right  = nearVal * (m20 + 1.0f) / m00;
}

/*!
 * @brief decomposes top and bottom values of perspective projection.
 *        y stands for y axis (top / botom axis)
 *
 * @param[in]  proj   perspective projection matrix
 * @param[out] top    top
 * @param[out] bottom bottom
 */
CGLM_INLINE
void
glm_persp_decomp_y(mat4 proj,
                   float * __restrict top,
                   float * __restrict bottom) {
  float nearVal, m21, m11;

  m21 = proj->data[2].data[1];
  m11 = proj->data[1].data[1];

  nearVal = proj->data[3].data[2] / (proj->data[3].data[3] - 1.0f);
  *bottom = nearVal * (m21 - 1) / m11;
  *top    = nearVal * (m21 + 1) / m11;
}

/*!
 * @brief decomposes near and far values of perspective projection.
 *        z stands for z axis (near / far axis)
 *
 * @param[in]  proj    perspective projection matrix
 * @param[out] nearVal near
 * @param[out] farVal  far
 */
CGLM_INLINE
void
glm_persp_decomp_z(mat4 proj,
                   float * __restrict nearVal,
                   float * __restrict farVal) {
  float m32, m22;

  m32 = proj->data[3].data[2];
  m22 = proj->data[2].data[2];

  *nearVal = m32 / (m22 - 1.0f);
  *farVal  = m32 / (m22 + 1.0f);
}

/*!
 * @brief decomposes far value of perspective projection.
 *
 * @param[in]  proj   perspective projection matrix
 * @param[out] farVal far
 */
CGLM_INLINE
void
glm_persp_decomp_far(mat4 proj, float * __restrict farVal) {
  *farVal = proj->data[3].data[2] / (proj->data[2].data[2] + 1.0f);
}

/*!
 * @brief decomposes near value of perspective projection.
 *
 * @param[in]  proj    perspective projection matrix
 * @param[out] nearVal near
 */
CGLM_INLINE
void
glm_persp_decomp_near(mat4 proj, float * __restrict nearVal) {
  *nearVal = proj->data[3].data[2] / (proj->data[2].data[2] - 1.0f);
}

/*!
 * @brief returns field of view angle along the Y-axis (in radians)
 *
 * if you need to degrees, use glm_deg to convert it or use this:
 * fovy_deg = glm_deg(glm_persp_fovy(projMatrix))
 *
 * @param[in] proj perspective projection matrix
 */
CGLM_INLINE
float
glm_persp_fovy(mat4 proj) {
  return 2.0f * atanf(1.0f / proj->data[1].data[1]);
}

/*!
 * @brief returns aspect ratio of perspective projection
 *
 * @param[in] proj perspective projection matrix
 */
CGLM_INLINE
float
glm_persp_aspect(mat4 proj) {
  return proj->data[1].data[1] / proj->data[0].data[0];
}

/*!
 * @brief returns sizes of near and far planes of perspective projection
 *
 * @param[in]  proj perspective projection matrix
 * @param[in]  fovy fovy (see brief)
 * @param[out] dest sizes order: [Wnear, Hnear, Wfar, Hfar]
 */
CGLM_INLINE
void
glm_persp_sizes(mat4 proj, float fovy, vec4 dest) {
  float t, a, nearVal, farVal;

  t = 2.0f * tanf(fovy * 0.5f);
  a = glm_persp_aspect(proj);

  glm_persp_decomp_z(proj, &nearVal, &farVal);

  dest->data[1]  = t * nearVal;
  dest->data[3]  = t * farVal;
  dest->data[0]  = a * dest->data[1];
  dest->data[2]  = a * dest->data[3];
}

#endif /* cglm_vcam_h */
