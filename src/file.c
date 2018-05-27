//
// Created by Firehorse on 22/05/2018.
//

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "file.h"


FILE *open_file(const char *file_path, int *file_len) {
    FILE *file = fopen(file_path, "rb");
    if (!file) {
        return null;
    }

    fseek(file, 0, SEEK_END);
    long len = ftell(file);
    fseek(file, 0, SEEK_SET);

    *file_len = len;
    return file;
}

bool read_file(FILE *file, uint file_len, byte *buffer, uint buffer_size) {
    if (file_len > buffer_size) {
        return false;
    } else {
        fread(buffer, sizeof(byte), file_len, file);
        return true;
    }
}

file_status_t read_file_data(const char *file_path, byte *buffer, uint buffer_size, _OUT_ uint *file_length) {
    FILE *file = open_file(file_path, (int *) file_length);
    
    file_status_t result = FILE_OK;
    if (!file) {
        result = FILE_NOT_FOUND;
    } else {
        bool file_read = read_file(file, *file_length, buffer, buffer_size);
        if (!file_read) {
            // If didn't read file, it means the buffer was too small
            // since we already validated that the file exists
            result = BUFFER_TOO_SMALL;
        }
    }

    fclose(file);
    return result;
}

file_status_t read_file_string(const char *file_path, char *buffer, uint buffer_size, _OUT_ uint *file_length) {
    file_status_t result = read_file_data(file_path, (byte *) buffer, buffer_size, file_length);
    if (result == FILE_OK) {
        buffer[*file_length] = '\0';
        *file_length += 1;
    }

    return result;
}

char *read_file_string_alloc(const char *file_path, _OUT_ uint *file_length) {
    FILE *file = open_file(file_path, (int *) file_length);
    if (!file) {
        return null;
    }

    uint buffer_size = *file_length + 1; // Add one for the \0 at the end
    char *buffer = (char *) calloc((uint) buffer_size , sizeof(char));
    read_file(file, *file_length, (byte *) buffer, buffer_size);

    buffer[*file_length] = '\0';
    *file_length = buffer_size;

    fclose(file);

    return buffer;
}

void free_file_string(char *file_data) {
    free(file_data);
}

byte *read_file_data_alloc(const char *file_path, _OUT_ uint *file_length) {
    int len;
    FILE *file = open_file(file_path, &len);
    if (!file) {
        return null;
    }
    
    byte *buffer = (byte *) calloc((uint) len, sizeof(byte));
    read_file(file, len, buffer, len);
    
    fclose(file);

    *file_length = (uint) len;

    return buffer;
}

void free_file_data(byte *file_data) {
    free(file_data);
}