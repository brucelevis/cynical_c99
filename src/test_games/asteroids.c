//
// Created by temdisponivel on 09/06/2018.
//

#include <engine.h>
#include <resource_manager.h>
#include <input.h>
#include "graphics.h"

#define DATA_FOLDER "data/tests/asteroids/"
#define TEXTURE_DATA_FOLDER DATA_FOLDER "textures"

#define PLAYER_ROTATION_SPEED 60
#define PLAYER_SPEED 1
#define DRAG 1

typedef struct player {
    texture_renderer_t texture;
    transform_t transform;
    vec3_t velocity;
} player_t;

typedef enum direction {
    LEFT,
    RIGHT
} direction_t;

camera_t game_camera;
player_t player;

void update_player() {

    direction_t direction = LEFT;
    bool rotated = false;
    if (get_key_down(KEY_A)) {
        direction = LEFT;
        rotated = true;
    } else if (get_key_down(KEY_D)) {
        direction = RIGHT;
        rotated = true;
    }
    
    if (rotated) {
        const vec3_t axis = VEC3_MAKE_FORWARD();

        float angle = RAD(PLAYER_ROTATION_SPEED * delta_time);
        if (direction == LEFT) {
            angle = -angle;
        }

        quat_t rotation_quat;
        quat_angle_axis(&axis, angle, &rotation_quat);
        quat_multiply(&player.transform.rotation, &rotation_quat, &player.transform.rotation);
    }

    vec3_t acceleration = VEC3_MAKE_ZERO();
    if (get_key_down(KEY_W)) {
        vec3_t up;
        trans_get_up(&player.transform, &up);
        vec3_scale(&up, PLAYER_SPEED * delta_time, &acceleration);
    } else if (get_key_down(KEY_S)) {
        vec3_t down;
        trans_get_down(&player.transform, &down);
        vec3_scale(&down, (PLAYER_SPEED * delta_time), &acceleration);
    } else {
        vec3_t down;
        trans_get_down(&player.transform, &down);
        //vec3_scale(&down, DRAG * delta_time, &acceleration);
    }

    vec3_add(&player.velocity, &acceleration, &player.velocity);
    
    vec3_add(&player.transform.position, &player.velocity, &player.transform.position);    
}

int main() {
    if (init_engine() != ENGINE_INIT_OK) {
        return -1;
    }
    
    create_camera_orthographic_default(&game_camera);
    trans_identity(&player.transform);

    texture_t *ball_texture = get_texture_resource(TEXTURE_DATA_FOLDER "/player_ship.png");
    material_t *material = get_material_resource("data/tests/pong/pong_sprite_material.mat_def");
    create_texture_renderer(ball_texture, material, &player.texture);
    
    
    game_camera.clear_color = COLOR_MAKE_BLACK();
    
    do {
        start_frame();
        
        // ========= UPDATE

        update_player();
        
        // ========== DRAWING
        
        use_camera(&game_camera);
        
        draw_texture_renderer(&player.texture, &player.transform);
        
        end_frame();
    } while (!should_quit);
    
    return 1;
}