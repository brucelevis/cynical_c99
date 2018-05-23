//
// Created by Firehorse on 22/05/2018.
//

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "file.h"

// TODO(temdisponivel): Maybe we should set allocators instead of not reading the
// file in case of buffer too small
file_status_t read_file_data(const char *file_path, byte *buffer, uint buffer_size, _OUT_ uint *file_length) {
    FILE *file = fopen(file_path, "r");
    if (!file) {
        return FILE_NOT_FOUND;
    }

    fseek(file, 0, SEEK_END);
    long len = ftell(file);
    fseek(file, 0, SEEK_SET);

    file_status_t result;
    if (len > buffer_size) {
        result = BUFFER_TOO_SMALL;
    } else {
        *file_length = len;
        fread(buffer, sizeof(byte), (uint) len, file);
        result = FILE_OK;
    }

    fclose(file);
    return result;
}