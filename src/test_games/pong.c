//
// Created by temdisponivel on 04/06/2018.
//

#include <malloc.h>
#include "engine.h"
#include "graphics.h"
#include "resource_manager.h"
#include "input.h"
#include "math/maths.h"

#define DATA_FOLDER "data/tests/pong/"

const int RACKET_SPEED = 10;

typedef struct entity {
    transform_t transform;
    texture_renderer_t texture;
    rect_t rect;
    vec2_t velocity;
} entity_t;

entity_t left_racket;
entity_t right_racket;
entity_t ball;

camera_t game_camera;

void setup_scene() {
    material_t *material = get_material_resource(DATA_FOLDER "pong_sprite_material.mat_def");

    texture_t *racket_texture = get_texture_resource(DATA_FOLDER "racket.png");
    texture_t *ball_texture = get_texture_resource(DATA_FOLDER "ball.png");

    create_texture_renderer(racket_texture, material, &left_racket.texture);
    create_texture_renderer(racket_texture, material, &right_racket.texture);
    create_texture_renderer(ball_texture, material, &ball.texture);
    
    left_racket.rect.size = racket_texture->size;
    right_racket.rect.size = racket_texture->size;
    ball.rect.size = ball_texture->size;
    
    trans_identity(&left_racket.transform);
    trans_identity(&right_racket.transform);
    trans_identity(&ball.transform);
    
    left_racket.transform.position.x = -screen_size.x / 2.f;
    right_racket.transform.position.x = screen_size.x / 2.f;

    create_camera_orthographic_default(screen_size.width / screen_size.height, &game_camera);
    //create_camera_perspective_default(screen_size.width / screen_size.height, &game_camera);]
}

void move_entity(entity_t *entity) {
    entity->transform.position.x += entity->velocity.x;
    entity->transform.position.y += entity->velocity.y;
    
    entity->rect.bottom_left = VEC2_FROM_VEC3(entity->transform.position);
}

void update_entities() {
    if (get_key_down(KEY_W)) {
        left_racket.velocity.y = RACKET_SPEED;
        if (left_racket.transform.position.y < (screen_size.y / 2.f))
            move_entity(&left_racket);
    }

    if (get_key_down(KEY_S)) {
        left_racket.velocity.y = -RACKET_SPEED;
        move_entity(&left_racket);
    }

    if (get_key_down(KEY_UP)) {
        right_racket.velocity.y = RACKET_SPEED;
        move_entity(&right_racket);
    }

    if (get_key_down(KEY_DOWN)) {
        right_racket.velocity.y = -RACKET_SPEED;
        move_entity(&right_racket);
    }
}

void draw_entities() {
    draw_texture_renderer(&left_racket.texture, &left_racket.transform);
    draw_texture_renderer(&right_racket.texture, &right_racket.transform);
    draw_texture_renderer(&ball.texture, &ball.transform);
}

int main() {
    
    // TODO(temdisponivel): Add hotreloader
    
    if (init_engine() != ENGINE_INIT_OK) {
        return -1;
    }
    
    // MOVE(temdisponivel): Move this update screen_size to a engine function
    int width, height;
    glfwGetWindowSize(game_window, &width, &height);
    screen_size.width = width;
    screen_size.height = height;
    
    setup_scene();
    
    while (!glfwWindowShouldClose(game_window)) {        
        update_input();
        
        glfwGetWindowSize(game_window, &width, &height);
        screen_size.width = width;
        screen_size.height = height;
        
        glViewport(0, 0, width, height);
        
        update_entities();
        
        use_camera(&game_camera);
        
        draw_entities();
        
        glfwSwapBuffers(game_window);
    }
    
    return 0;
}