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
typedef char byte;
typedef unsigned char ushort;
#define null NULL
#define _OUT_

#define TEMP_STR_BUFFER_LEN 1024
#define CREATE_TEMP_STR_BUFFER() byte TEMP_BUFFER[TEMP_STR_BUFFER_LEN]

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

#endif //RAW_GL_COMMON_H
