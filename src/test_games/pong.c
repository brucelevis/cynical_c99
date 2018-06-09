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

const int RACKET_SPEED = 500;
const int BALL_SPEED = 300;
double delta_time;
float aspect_ratio;
vec2_t half_screen_size;

float left_points, right_points;

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

void move_entity(entity_t *entity) {
    entity->transform.position.x += entity->velocity.x * delta_time;
    entity->transform.position.y += entity->velocity.y * delta_time;

    entity->rect.bottom_left = entity->transform.position.xy;
}

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
    
    float aspect_ratio = screen_size.width / screen_size.height;
    left_racket.transform.position.x = ((-screen_size.width / 2.f) * aspect_ratio) + racket_texture->size.width / 2.f;
    right_racket.transform.position.x = ((screen_size.width / 2.f) * aspect_ratio) - racket_texture->size.width / 2.f;

    create_camera_orthographic_default(screen_size.width / screen_size.height, &game_camera);
    //create_camera_perspective_default(screen_size.width / screen_size.height, &game_camera);]
    
    ball.velocity.x = BALL_SPEED;
    ball.velocity.y = BALL_SPEED;
    
    move_entity(&left_racket);
    move_entity(&right_racket);
    
    left_points = 0;
    right_points = 0;
}

typedef enum direction {
    UP,
    DOWN
} direction_t;

bool can_move_racket(const entity_t *racket, direction_t direction) {
    float y = racket->transform.position.y;
    if (direction == UP) {
        y += racket->texture.size.height / 2.f;
        return y < half_screen_size.height;
    } else {
        y -= racket->texture.size.height / 2.f;
        return y > -half_screen_size.height;
    }
}

void update_entities() {

    left_racket.transform.position.x = (-half_screen_size.width) + left_racket.texture.size.width / 2.f;
    right_racket.transform.position.x = (half_screen_size.width) - right_racket.texture.size.width / 2.f;
    
    if (get_key_down(KEY_W)) {
        if (can_move_racket(&left_racket, UP)) {
            left_racket.velocity.y = RACKET_SPEED;
            move_entity(&left_racket);
        }
    }

    if (get_key_down(KEY_S)) {
        if (can_move_racket(&left_racket, DOWN)) {
            left_racket.velocity.y = -RACKET_SPEED;
            move_entity(&left_racket);
        }
    }
    
    if (get_key_down(KEY_UP)) {
        if (can_move_racket(&right_racket, UP)) {
            right_racket.velocity.y = RACKET_SPEED;
            move_entity(&right_racket);
        }
    }

    if (get_key_down(KEY_DOWN)) {
        if (can_move_racket(&right_racket, DOWN)) {
            right_racket.velocity.y = -RACKET_SPEED;
            move_entity(&right_racket);
        }
    }

    vec2_t top_right = rect_get_top_right(&ball.rect);
    if (ball.rect.bottom_left.y <= -half_screen_size.height ) {
        ball.velocity.y *= -1;
    } else if (top_right.y >= half_screen_size.y) {
        ball.velocity.y *= -1;
    }
    
    if (rect_touch(&left_racket.rect, &ball.rect)) {
        ball.velocity.x *= -1;
    } else if (rect_touch(&right_racket.rect, &ball.rect)) {
        ball.velocity.x *= -1;
    } else {
        if (ball.rect.bottom_left.x >= half_screen_size.width) {
            left_points++;
            printf("Left scored!\n");
            ball.transform.position = VEC3_MAKE_ZERO();
        } else if (ball.rect.bottom_left.x <= -half_screen_size.width) {
            right_points++;
            printf("Right scored!\n");
            ball.transform.position = VEC3_MAKE_ZERO();
        }
    }
    
    move_entity(&ball);
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

    double start_time = 0, end_time = 0;
    while (!glfwWindowShouldClose(game_window)) {
        delta_time = end_time - start_time;
        start_time = glfwGetTime();
        update_input();
        
        glfwGetWindowSize(game_window, &width, &height);
        screen_size.width = width;
        screen_size.height = height;
        aspect_ratio = screen_size.width / screen_size.height;
        vec2_scale(&screen_size, .5f, &half_screen_size);
        half_screen_size.x *= aspect_ratio;
        
        create_camera_orthographic_default(aspect_ratio, &game_camera);
        
        glViewport(0, 0, width, height);
        
        update_entities();
        
        use_camera(&game_camera);
        
        draw_entities();
        
        glfwSwapBuffers(game_window);
        end_time = glfwGetTime();
    }
    
    return 0;
}