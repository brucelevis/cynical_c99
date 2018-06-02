//
// Created by temdisponivel on 01/06/2018.
//

#ifndef RAW_GL_MEMORY_H
#define RAW_GL_MEMORY_H

#include "common.h"

typedef struct custom_memory {
    void *buffer;
    uint buffer_byte_size;
    
    void *current_free_offset_ptr;
    
    int water_marker;
} custom_memory_t;

void initialize_memories(uint frame_buffer_size, uint persistence_buffer_size);
void reset_buffer(custom_memory_t *memory);

void reset_frame_buffer();

void create_custom_memory(uint desired_size, custom_memory_t *dest);
void free_custom_memory(custom_memory_t *memory);

void *alloc_memory(custom_memory_t *memory, uint size);
void free_memory(custom_memory_t *memory, void *pointer);

void *alloc_frame_memory(uint size);

void alloc_persistent_memory(uint size);
void free_persistent_memory(void *pointer);


#endif //RAW_GL_MEMORY_H
