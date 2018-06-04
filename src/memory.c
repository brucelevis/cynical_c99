//
// Created by temdisponivel on 02/06/2018.
//

#include <malloc.h>
#include <mem.h>
#include "memory.h"

memory_pool_t small_memory_pool;
memory_pool_t medium_memory_pool;
memory_pool_t big_memory_pool;
memory_pool_t gigantic_memory_pool;
memory_pool_t enormous_memory_pool;

void create_default_memory_pool() {
    create_memory_pool(SMALL_MEMORY_POOL_SIZE, SMALL_CHUNK_SIZE, &small_memory_pool);
    create_memory_pool(MEDIUM_MEMORY_POOL_SIZE, MEDIUM_CHUNK_SIZE, &medium_memory_pool);
    create_memory_pool(BIG_MEMORY_POOL_SIZE, BIG_CHUNK_SIZE, &big_memory_pool);
    create_memory_pool(GIGANTIC_MEMORY_POOL_SIZE, GIGANTIC_CHUNK_SIZE, &gigantic_memory_pool);
    create_memory_pool(ENORMOUS_MEMORY_POOL_SIZE, ENORMOUS_CHUNK_SIZE, &enormous_memory_pool);
}

void create_memory_pool(uint full_size, uint chunk_size, memory_pool_t *dest) {
    ASSERT(full_size % chunk_size == 0);

    dest->data = malloc(full_size);
    ASSERT(dest->data);

    uint chunks_len = full_size / chunk_size;

    dest->all_chunks = malloc(sizeof(memory_chunk_t) * chunks_len);
    dest->all_chunks_len = chunks_len;
    dest->free_list = &dest->all_chunks[0];
    dest->chunk_size = chunk_size;

    for (int i = 0; i < chunks_len - 1; ++i) {
        dest->all_chunks[i].data = dest->data + (i * chunk_size);
        dest->all_chunks[i].next = &dest->all_chunks[i + 1];
    }

    dest->all_chunks[chunks_len - 1].data = dest->data + ((chunks_len - 1) * chunk_size);
    dest->all_chunks[chunks_len - 1].next = null;
}

void *memory_alloc(memory_pool_t *memory, uint size) {
    ASSERT(size < memory->chunk_size);
    ASSERT(memory->free_list);   
    
    if (size >= memory->chunk_size) {
        printf("ALO\n");
    }

    memory_chunk_t *result = memory->free_list;
    memory->free_list = result->next;

    return result->data;
}

void memory_free(memory_pool_t *memory, void *data) {
    ulong ptr = (data - memory->data);
    ulong index = ptr / memory->chunk_size;
    
    if (memory->free_list) {
        memory->all_chunks[index].next = memory->free_list;
    }

    memory->free_list = &memory->all_chunks[index];
}