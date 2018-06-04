//
// Created by Firehorse on 22/05/2018.
//

#ifndef RAW_GL_FILE_H
#define RAW_GL_FILE_H

#include "common.h"

typedef enum {
    FILE_NOT_FOUND = -1,
    BUFFER_TOO_SMALL = -2,
    FILE_OK = 1,
} file_status_t;

file_status_t read_file_data(const char *file_path, byte *buffer, uint buffer_size,  uint *file_length);

file_status_t read_file_string(const char *file_path, char *buffer, uint buffer_size,  uint *file_length);

byte *read_file_data_alloc(const char *file_path,  uint *file_length);
void free_file_data(byte *file_data);

#endif //RAW_GL_FILE_H
