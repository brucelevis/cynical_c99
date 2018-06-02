//
// Created by temdisponivel on 02/06/2018.
//

#include <malloc.h>
#include "memory.h"

custom_memory_t _frame_buffer;
custom_memory_t _persistent_buffer;

void initialize_memories(uint frame_buffer_size, uint persistence_buffer_size) {
    create_custom_memory(frame_buffer_size, &_frame_buffer);
    create_custom_memory(persistence_buffer_size, &_persistent_buffer);
}

void reset_buffer(custom_memory_t *memory) {
    memory->current_free_offset_ptr = null;
}

void reset_frame_buffer() {
    reset_buffer(&_frame_buffer);
}

void create_custom_memory(uint desired_size, custom_memory_t *dest) {
    dest->buffer = malloc(desired_size);
    ASSERT(dest->buffer);
    dest->buffer_byte_size = desired_size;
    dest->current_free_offset_ptr = null;
    dest->water_marker = 0;
}

void free_custom_memory(custom_memory_t *memory) {
    reset_buffer(memory);
    
    free(memory->buffer);
    memory->buffer = null;
    memory->buffer_byte_size = 0;
}

void *alloc_memory(custom_memory_t *memory, uint size) {
    void *end_of_memory = memory->current_free_offset_ptr + size;
    ASSERT(end_of_memory < (memory->buffer + memory->buffer_byte_size));
    void *result = memory->current_free_offset_ptr;
    memory->current_free_offset_ptr += size;
    
    if ((int) memory->current_free_offset_ptr > memory->water_marker) {
        memory->water_marker = (int) memory->current_free_offset_ptr;
    }

    return result;
}

void free_memory(custom_memory_t *memory, void *pointer) {
    
}

void *alloc_frame_memory(uint size) {
    alloc_memory(&_frame_buffer, size);
}

void alloc_persistent_memory(uint size) {
    alloc_memory(&_persistent_buffer, size);
}

void free_persistent_memory(void *pointer) {
    free_memory(&_persistent_buffer, pointer);
}
