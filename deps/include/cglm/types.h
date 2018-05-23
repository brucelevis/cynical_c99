/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef cglm_types_h
#define cglm_types_h

#if defined(_MSC_VER)
/* do not use alignment for older visual studio versions */
#if _MSC_VER < 1913 /*  Visual Studio 2017 version 15.6  */
#  define CGLM_ALL_UNALIGNED
#  define CGLM_ALIGN(X) /* no alignment */
#else
#  define CGLM_ALIGN(X) __declspec(align(X))
#endif
#else
#  define CGLM_ALIGN(X) __attribute((aligned(X)))
#endif

#ifndef CGLM_ALL_UNALIGNED
#  define CGLM_ALIGN_IF(X) CGLM_ALIGN(X)
#else
#  define CGLM_ALIGN_IF(X) /* no alignment */
#endif

typedef struct {
    union {
        struct {
            float x;
            float y;
        };
        float data[2];
    };
} *vec2, vec2_t;

typedef CGLM_ALIGN_IF(8)  struct {
    union {
        struct {
            float x;
            float y;
            float z;
        };
        float data[3];
    };
} *vec3, vec3_t;

typedef struct {
    union {
        struct {
            float x;
            float y;
            float z;
        };
        int data[3];
    };
} *ivec3, ivec3_t;

typedef CGLM_ALIGN_IF(16) struct {
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
} *vec4, vec4_t;

typedef struct {
    union {
        struct {
            vec3 x;
            vec3 y;
            vec3 z;
        };
        vec3_t data[3];
    };
} *mat3, mat3_t;

typedef CGLM_ALIGN_IF(16) struct {
    union {
        struct {
            vec4 x;
            vec4 y;
            vec4 z;
            vec4 w;
        };
        vec4_t data[4];
    };
} *mat4, mat4_t;

typedef vec4 versor;

#define CGLM_PI    ((float)M_PI)
#define CGLM_PI_2  ((float)M_PI_2)
#define CGLM_PI_4  ((float)M_PI_4)

#endif /* cglm_types_h */
