//
// Created by temdisponivel on 01/06/2018.
//

#ifndef RAW_GL_MEMORY_H
#define RAW_GL_MEMORY_H

#include "common.h"

#define CHUNK_SIZE 64
#define DEFAULT_MEMORY_POOL_SIZE (CHUNK_SIZE * 1024)  

typedef struct memory_chunk {
    void *data;
    struct memory_chunk *next; 
} memory_chunk_t;

typedef struct memory {
    void *data;
    
    memory_chunk_t *all_chunks;
    uint all_chunks_len;
    
    memory_chunk_t *free_list;
} memory_pool_t;

void create_default_memory_pool();

void create_memory(uint full_size, memory_pool_t *dest);

void *memory_alloc(memory_pool_t *memory, uint size);
void memory_free(memory_pool_t *memory, void *data);

void *memory_alloc_default(uint size);
void memory_free_default(void *data);

#endif //RAW_GL_MEMORY_H
