//
// Created by temdisponivel on 01/06/2018.
//

#ifndef RAW_GL_TEST_RESOURCE_MANAGER_H
#define RAW_GL_TEST_RESOURCE_MANAGER_H

#include "resource_manager.h"

void test() {
    texture_t *texture1 = get_texture_resource("data/textures/default.png");
    texture_t *texture2 = get_texture_resource("data/textures/default.png");
    
    ASSERT(texture1 == texture2);
    
    free_unused_resources();
    
    print_resources();
    
    free_texture_resource(texture1);
    free_texture_resource(texture1);

    free_unused_resources();
    
    print_resources();
}

#endif //RAW_GL_TEST_RESOURCE_MANAGER_H
