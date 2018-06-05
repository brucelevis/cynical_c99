//
// Created by temdisponivel on 03/06/2018.
//

#ifndef TEST_MEMORY
#define TEST_MEMORY

#include <mem.h>
#include <sys/types.h>
#include <sys\timeb.h>
#include <malloc.h>
#include <time.h>
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
    
    const int cont = 10000;
    printf("ALLOCATE\n");
    
    clock_t malloc_start = clock();
    
    for (int i = 0; i < cont; ++i) {
        test_struct_t *test = malloc(sizeof(test_struct_t));
        
        strcpy(test->name, "TEMDISPONIVEL");
        test->a = 1;
        test->pointer = test;
    }

    clock_t malloc_end = clock();

    clock_t pool_start = clock();

    for (int i = 0; i < cont; ++i) {

        test_struct_t *test = medium_memory_alloc(sizeof(test_struct_t));
        
        strcpy(test->name, "TEMDISPONIVEL");
        test->a = 1;
        test->pointer = test;
    }

    clock_t pool_end = clock();
    
    double malloc_duration = malloc_end - malloc_start;
    double pool_duration = pool_end - pool_start;
    
    printf("Malloc diff: %f - Pool time %f\n", malloc_duration / CLOCKS_PER_SEC, pool_duration/ CLOCKS_PER_SEC);
    return;
    /*
    
    printf("FREE\n");

    for (int j = 0; j < 200; ++j) {
        if (j % 2 == 0) {
            medium_memory_free(values[j]);
        }
    }

    for (int j = 0; j < 200; ++j) {
        if (j % 2 != 0) {
            medium_memory_free(values[j]);
        }
    }

    printf("ALLOCATE\n");
    
    for (int i = 0; i < cont; ++i) {

        test_struct_t *test = medium_memory_alloc(sizeof(test_struct_t));
        values[cont] = test;

        strcpy(test->name, "TEMDISPONIVEL 2");
        test->a = 3;
        test->pointer = test + 1;

        printf("%i:\n", i);
        print_test_struct(test);
    }
    
    printf("END\n");


    printf("TEMP ALLOCATE\n");

    for (int i = 0; i < cont; ++i) {

        test_struct_t *test = memory_temp_alloc_default(sizeof(test_struct_t));
        values[i] = test;

        strcpy(test->name, "TEMDISPONIVEL");
        test->a = 1;
        test->pointer = test;

        printf("%i:\n", i);
        print_test_struct(test);
    }

    printf("TEMP FREE\n");

    reset_temp_memory_default();
    
    printf("TEMP ALLOCATE\n");

    for (int i = 0; i < cont; ++i) {

        test_struct_t *test = memory_temp_alloc_default(sizeof(test_struct_t));
        values[cont] = test;

        strcpy(test->name, "TEMDISPONIVEL 2");
        test->a = 3;
        test->pointer = test + 1;

        printf("%i:\n", i);
        print_test_struct(test);
    }

    printf("END\n");    */
}

#endif