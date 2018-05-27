//
// Created by temdisponivel on 27/05/2018.
//

#include "string_helper.h"

// TODO(temdisponivel): Add custom allocators support

long hash_string(const char *string) {
    char current;
    unsigned long hash = 5381;

    int index = 0;
    do {
        current = string[index++];
        hash = ((hash << 5) + hash) + current; /* hash * 33 + c */
    } while (current != '\0');
}