//
// Created by temdisponivel on 03/06/2018.
//

#ifndef TEST_MEMORY
#define TEST_MEMORY

#include <mem.h>
#include "memory.h"

typedef struct test_struct {
    uint a;
    char name[DEFAULT_NAME_LEN];
    void *pointer;
} test_struct_t;

void print_test_struct(test_struct_t *test) {
    printf("name: '%s'\na: '%i'\npointer: '%i'\n", test->name, test->a, test->pointer);
}

void test_memory() {
    create_default_memory_pool();

    printf("size: %i", sizeof(test_struct_t));
    
    const int cont = 200;
    test_struct_t *values[cont];

    printf("ALLOCATE\n");
    
    for (int i = 0; i < cont; ++i) {

        test_struct_t *test = memory_alloc_default(sizeof(test_struct_t));
        values[i] = test;
        
        strcpy(test->name, "TEMDISPONIVEL");
        test->a = 1;
        test->pointer = test;

        printf("%i:\n", i);
        print_test_struct(test);
    }
    
    printf("FREE\n");

    for (int j = 0; j < 200; ++j) {
        if (j % 2 == 0) {
            memory_free_default(values[j]);
        }
    }

    for (int j = 0; j < 200; ++j) {
        if (j % 2 != 0) {
            memory_free_default(values[j]);
        }
    }

    printf("ALLOCATE\n");
    
    for (int i = 0; i < cont; ++i) {

        test_struct_t *test = memory_alloc_default(sizeof(test_struct_t));
        values[cont] = test;

        strcpy(test->name, "TEMDISPONIVEL 2");
        test->a = 3;
        test->pointer = test + 1;

        printf("%i:\n", i);
        print_test_struct(test);
    }
}

#endif