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

#define TEMP_MEMORY_SIZE (MEGA_BYTE * 4)

typedef struct memory_pool {
    void *data;
    uint size;
    uint capacity;
} memory_pool_t;

memory_pool_t __temp_mem_pool;

INLINE void make_pool(memory_pool_t *pool, uint size);
INLINE void *allocate(memory_pool_t *pool, uint size);
INLINE void clear_pool(memory_pool_t *pool);

INLINE void *heap_alloc(uint size);
INLINE void heap_free(void *ptr);


INLINE void make_pool(memory_pool_t *pool, uint size) {
    pool->data = malloc(size);
    pool->capacity = size;
    pool->size = 0;
}

INLINE void *allocate(memory_pool_t *pool, uint size) {
    if (pool->size + size > pool->capacity) {
        return null;
    } else {
        void *result = pool->data;
        pool->size += size;
        pool->data += size;
        return result;
    }
}

INLINE void clear_pool(memory_pool_t *pool) {
    pool->data -= pool->size;
    pool->size = 0;
}

// TODO(temdisponivel): Go through every use of this and see if we can convert this into a memory pool
INLINE void *heap_alloc(uint size) {
    return malloc(size);
}

INLINE void heap_free(void *ptr) {
    free(ptr);
}

#endif //RAW_GL_MEMORY_H
