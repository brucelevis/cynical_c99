//
// Created by temdisponivel on 26/05/2018.
//

#include "cglm/affine-mat.h" 
#include "cglm/affine.h" 
#include "cglm/quat.h"
#include "maths.h"
#include "cglm/cam.h"
#include "cglm/mat4.h"

void assert(int shader) {
    mat4 view, proj, view_proj, model, mvp;
    vec3 eye, dir, up, pos, axis, scale;
    
    eye[0] = 0;
    eye[1] = 0;
    eye[2] = 0;
    
    dir[0] = 0;
    dir[1] = 0;
    dir[2] = -1;
    
    up[0] = 0;
    up[1] = 1;
    up[2] = 0;

    axis[0] = 0;
    axis[1] = 1;
    axis[2] = 0;

    pos[0] = 0;
    pos[1] = 0;
    pos[2] = -10;

    scale[0] = 2;
    scale[1] = 2;
    scale[2] = 2;
    
    glm_look(eye, dir, up, view);
    
    glm_perspective(RAD(45), 16 / 9.f, 0.01f, 10000.f, proj);
    
    glm_mat4_identity(model);
    glm_scale(model, scale);
    glm_rotate(model, RAD(0), axis);
    glm_translate(model, pos);
    
    mat4_t t_MVP, t_view, t_proj, t_view_proj, t_model;
    vec3_t t_dir, t_pos, t_up;

    mat4_identity(&t_MVP);
    mat4_identity(&t_view);
    mat4_identity(&t_proj);
    mat4_identity(&t_model);

    quat_t rot;
    vec3_t t_axis = VEC3_MAKE_UP();
    quat_angle_axis(&t_axis, RAD(0), &rot);

    vec3_t trans_pos = vec3_make(0, 0, -2);
    vec3_t trans_scale = vec3_make(2, 2, 2);
    transform_t trans = trans_make(&trans_pos, &trans_scale, &rot);
    trans_get_mat4(&trans, &t_model);

    vec3_set(0, 0, 100, &t_pos);
    vec3_set(0, 0, -1, &t_dir);
    vec3_set(0, 1, 0, &t_up);

    mat4_look(&t_pos, &t_dir, &t_up, &t_view);
    mat4_perspective(RAD(45), 16 / 9.f, 0.01f, 10000.f, &t_proj);

    glm_mat4_mul(proj, view, view_proj);
    glm_mat4_mul(view_proj, model, mvp);

    mat4_mul(&t_proj, &t_view, &t_view_proj);
    mat4_mul(&t_view_proj, &t_model, &t_MVP);

    float *values = (float *) &mvp;
    float *t_values = (float *) &t_MVP;

    for (int i = 0; i < 16; ++i) {
        if (values[i] != t_values[i]) {
            fprintf(stderr, "Value at '%f != %f' is different. Index: %i!\n", t_values[i], t_values[i], i);
        }
    }

    int loc = glGetUniformLocation(shader, "MVP");
    glUniformMatrix4fv(loc, 1, GL_FALSE, values);
    CHECK_GL_ERROR();
}

