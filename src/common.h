//
// Created by Firehorse on 22/05/2018.
//

#ifndef RAW_GL_COMMON_H
#define RAW_GL_COMMON_H

#include <stdio.h>

typedef unsigned int uint;
typedef int bool;
#define true 1
#define false 0
typedef unsigned char byte;
typedef unsigned short ushort;
#define null NULL

#if defined(_MSC_VER)
#  define INLINE __forceinline
#else
#  define EXPORT __attribute__((visibility("default")))
#  define INLINE static inline __attribute((always_inline))
#endif

#define DATA_FOLDER "data/"
#define SHADER_FOLDER DATA_FOLDER"shaders/"
#define TEXTURE_FOLDER DATA_FOLDER"textures/"

#define DEFAULT_FILE_NAME_LEN 256
#define DEFAULT_NAME_LEN 32

#define TEMP_STR_BUFFER_LEN 2048
#define CREATE_TEMP_STR_BUFFER() CREATE_TEMP_NAMED_STR_BUFFER(TEMP_BUFFER) 
#define CREATE_TEMP_NAMED_STR_BUFFER(name) char name[TEMP_STR_BUFFER_LEN]
#define CLEAR_TEMP_NAMED_STR_BUFFER(name) memset(name, 0, TEMP_STR_BUFFER_LEN * sizeof(char))

#define array_move_to_left(array, array_len, start_index) {\
    uint len = (*(array_len));\
    for (int j = (start_index); j < len; ++j) {\
        (array)[j] = (array)[j + 1];\
    }\
    (*(array_len))--;\
}\

#define array_add(array, length, count, value_to_add) {\
    ASSERT((length) > ((*(count)) + 1));\
    (array)[(*(count))++] = (value_to_add);\
}\

#define array_remove(array, count, value_to_remove) {\
    uint len = (*(count));\
    for (int i = len - 1; i >= 0; --i) {\
        int element = (array)[i];\
        if (element == (value_to_remove)) {\
            array_move_to_left((array), (count), i);\
        }\
    }\
}\

#ifdef DEV

#define PRINT_LINE_FILE(file) {\
    fprintf(file, "\n AT: %s:%i \n", __FILE__, __LINE__);\
}\

#define PRINT_LINE_ERROR() {\
    PRINT_LINE_FILE(stderr);\
}\

#define PRINT_LINE() {\
    PRINT_LINE(stdout);\
}\

#define ERROR(error) {\
    fprintf(stderr, error);\
    PRINT_LINE_ERROR();\
}\

#define ASSERT(expression) {\
    if (!(expression)) {\
        ERROR("Assert failed!")\
    }\
}\

#else

#define PRINT_LINE_FILE(file) 

#define PRINT_LINE_ERROR() 

#define PRINT_LINE() 

#define ERROR(error) 

#define ASSERT(expression) 

#endif

#endif //RAW_GL_COMMON_H
