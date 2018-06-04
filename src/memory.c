//
// Created by temdisponivel on 02/06/2018.
//

#include <malloc.h>
#include <mem.h>
#include "memory.h"

static memory_pool_t default_memory_pool;

void create_default_memory_pool() {
    create_memory(DEFAULT_MEMORY_POOL_SIZE, &default_memory_pool);
}

void create_memory(uint full_size, memory_pool_t *dest) {
    ASSERT(full_size % CHUNK_SIZE == 0);

    dest->data = malloc(full_size);
    ASSERT(dest->data);

    uint chunks_len = full_size / CHUNK_SIZE;

    dest->all_chunks = malloc(sizeof(memory_chunk_t) * chunks_len);
    dest->all_chunks_len = chunks_len;
    dest->free_list = &dest->all_chunks[0];

    for (int i = 0; i < chunks_len - 1; ++i) {
        dest->all_chunks[i].data = dest->data + (i * CHUNK_SIZE);
        dest->all_chunks[i].next = &dest->all_chunks[i + 1];
    }

    dest->all_chunks[chunks_len - 1].data = dest->data + ((chunks_len - 1) * CHUNK_SIZE);
    dest->all_chunks[chunks_len - 1].next = null;
}

void *memory_alloc(memory_pool_t *memory, uint size) {
    ASSERT(size < CHUNK_SIZE);
    ASSERT(memory->free_list);

    memory_chunk_t *result = memory->free_list;
    memory->free_list = result->next;

    return result->data;
}

void memory_free(memory_pool_t *memory, void *data) {
    ulong ptr = (data - memory->data);
    ulong index = ptr / CHUNK_SIZE;
    
    if (memory->free_list) {
        memory->all_chunks[index].next = memory->free_list;
    }

    memory->free_list = &memory->all_chunks[index];
}

void *memory_alloc_default(uint size) {
    return memory_alloc(&default_memory_pool, size);
}

void memory_free_default(void *data) {
    memory_free(&default_memory_pool, data);
}