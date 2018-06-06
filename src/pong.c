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

texture_t *racket_texture;
texture_t *ball_texture;

texture_renderer_t racket;
texture_renderer_t ball;

transform_t racket_left_trans;
transform_t racket_right_trans;
transform_t ball_trans;

camera_t game_camera;

int main() {
    if (init_engine() != ENGINE_INIT_OK) {
        return -1;
    }
    
    
    material_t *material = get_material_resource(DATA_FOLDER "pong_sprite_material.mat_def");    
    
    racket_texture = get_texture_resource(DATA_FOLDER "racket.png");
    ball_texture = get_texture_resource(DATA_FOLDER "ball.png");
    
    create_texture_renderer(racket_texture, material, &racket);
    create_texture_renderer(ball_texture, material, &ball);

    int width, height;
    glfwGetWindowSize(game_window, &width, &height);
    screen_size.width = width;
    screen_size.height = height;
    
    float half_width = width / 2.f;
    float half_height = height / 2.f;

    half_width = 1.f;
    half_height = 1.f;
    
    //create_camera_orthographic_default(screen_size.width / screen_size.height, &game_camera);
    create_camera_perspective_default(screen_size.width / screen_size.height, &game_camera);
        
    vec3_t zero = vec3_make(0, 0, -.02f);
    vec3_t one = VEC3_MAKE_ONE();
    quat_t quat = QUAT_MAKE_IDENTITY();
    
    racket_left_trans = racket_right_trans = ball_trans = trans_make(&zero, &one, &quat);
    
    while (!glfwWindowShouldClose(game_window)) {
        update_input();

        glfwGetWindowSize(game_window, &width, &height);
        screen_size.width = width;
        screen_size.height = height;

        glViewport(0, 0, width, height);
        
        if (get_key_down(KEY_RIGHT)) {
            racket_left_trans.position.x += 10;
        } else if (get_key_down(KEY_LEFT)) {
            racket_left_trans.position.x -= 10;
        } else if (get_key_down(KEY_UP)) {
            racket_left_trans.position.y += 10;
        } else if (get_key_down(KEY_DOWN)) {
            racket_left_trans.position.y -= 10;
        }

        if (get_key_down(KEY_D)) {
            game_camera.transform.position.x += 10;
        } else if (get_key_down(KEY_A)) {
            game_camera.transform.position.x -= 10;
        } else if (get_key_down(KEY_W)) {
            game_camera.transform.position.y += 10;
        } else if (get_key_down(KEY_S)) {
            game_camera.transform.position.y -= 10;
        }

        use_camera(&game_camera);
        
        //racket_left_trans.position.y = 0;
        //racket_left_trans.position.x = -(width / 2.f);
        
        vec3_t forward =  VEC3_MAKE_FORWARD();
        //quat_angle_axis(&forward, -RAD(30), &racket_left_trans.rotation);
    
        racket_left_trans.position.z = -1;


        printf("camera:\n");
        PRINT_VEC3(game_camera.transform.position);

        printf("racket:\n");
        PRINT_VEC3(racket_left_trans.position);
        
        //game_camera.transform.position.y = -(screen_size.y / 2.f);
        //vec3_set(2, 2, 2, &racket_left_trans.scale);
        /*
        racket_right_trans.position.y = height / 2;
        racket_right_trans.position.x = width - racket_texture->size.width;
        
        ball_trans.position.y = height / 2;
        ball_trans.position.x = (width / 2.f) - ball_texture->size.width / 2.f;*/
                
        //racket.size = vec2_make(width, height);

        draw_texture_renderer(&racket, &racket_left_trans);
        //draw_texture_renderer(&racket, &racket_right_trans);
        
        //draw_texture_renderer(&ball, &ball_trans);
        
        glfwSwapBuffers(game_window);
    }
    
    return 0;
}