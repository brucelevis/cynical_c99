//
// Created by temdisponivel on 01/06/2018.
//

#ifndef RAW_GL_MEMORY_H
#define RAW_GL_MEMORY_H

#include "common.h"

#define SMALL_CHUNK_SIZE 32
#define SMALL_MEMORY_POOL_SIZE (SMALL_CHUNK_SIZE * 1024)

#define MEDIUM_CHUNK_SIZE 128
#define MEDIUM_MEMORY_POOL_SIZE (MEDIUM_CHUNK_SIZE * 1024 * 1024)

#define BIG_CHUNK_SIZE 512
#define BIG_MEMORY_POOL_SIZE (BIG_CHUNK_SIZE * 1024)

#define GIGANTIC_CHUNK_SIZE 1024
#define GIGANTIC_MEMORY_POOL_SIZE (GIGANTIC_CHUNK_SIZE * 1024)

#define ENORMOUS_CHUNK_SIZE 2048
#define ENORMOUS_MEMORY_POOL_SIZE (ENORMOUS_CHUNK_SIZE * 1024)

#define TEMP_MEMORY_SIZE (1024 * 1024)

// TODO(temdisponivel): Should we actually support dynamic chunk size?!
// TODO(temdisponivel): Create a temporary memory alloction

typedef struct memory_chunk {
    void *data;
    struct memory_chunk *next; 
} memory_chunk_t;

typedef struct memory {
    void *data;
    
    memory_chunk_t *all_chunks;
    uint all_chunks_len;
    
    uint chunk_size;
    
    memory_chunk_t *free_list;
} memory_pool_t;

typedef struct temp_memory {
    void *data;
    uint data_size;
    
    void *current_free_ptr;
    uint used_size;
    
    uint water_mark;
} temp_memory_t;

memory_pool_t small_memory_pool;
memory_pool_t medium_memory_pool;
memory_pool_t big_memory_pool;
memory_pool_t gigantic_memory_pool;
memory_pool_t enormous_memory_pool;

temp_memory_t temporary_memory;

void create_default_memory_pool();
void create_temp_memory(uint size, temp_memory_t *dest);

void create_memory_pool(uint full_size, uint chunk_size, memory_pool_t *dest);

void *memory_alloc(memory_pool_t *memory, uint size);
void memory_free(memory_pool_t *memory, void *data);

#define small_memory_alloc(size) memory_alloc(&small_memory_pool, size)
#define small_memory_free(data) memory_free(&small_memory_pool, data)

#define medium_memory_alloc(size) memory_alloc(&medium_memory_pool, size)
#define medium_memory_free(data) memory_free(&medium_memory_pool, data)

#define big_memory_alloc(size) memory_alloc(&big_memory_pool, size)
#define big_memory_free(data) memory_free(&big_memory_pool, data)

#define gigantic_memory_alloc(size) memory_alloc(&gigantic_memory_pool, size)
#define gigantic_memory_free(data) memory_free(&gigantic_memory_pool, data)

#define enormous_memory_alloc(size) memory_alloc(&enormous_memory_pool, size)
#define enormous_memory_free(data) memory_free(&enormous_memory_pool, data);

void *memory_temp_alloc(temp_memory_t *memory, uint size);
void reset_temp_memory(temp_memory_t *memory);

#define memory_temp_alloc_default(size) memory_temp_alloc(&temporary_memory, size)
#define reset_temp_memory_default() reset_temp_memory(&temporary_memory)

#endif //RAW_GL_MEMORY_H
