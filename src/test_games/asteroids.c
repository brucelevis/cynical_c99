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
#define PLAYER_ACCELERATION .1f
#define DRAG .01f
#define VELOCITY_LIMIT .5f
#define MAX_PROJECTILES 100
#define MAX_ASTEROIDS 100
#define MAX_ENTITIES (MAX_PROJECTILES + MAX_ASTEROIDS + 1)

#define ASTEROID_VELOCITY .1f
#define PROJECTILE_VELOCITY .1f

typedef struct entity {
    texture_renderer_t texture;
    transform_t transform;
    vec3_t velocity;
    bool active;
} entity_t;

typedef enum direction {
    LEFT,
    RIGHT
} direction_t;

camera_t game_camera;

entity_t all_entities[MAX_ENTITIES];

entity_t *player;
entity_t *asteroids;
entity_t *projectiles;
int used_projectiles;

void screen_wrap(transform_t *trans) {
    vec2_t half_screen_size;
    vec2_scale(&screen_size, .5f, &half_screen_size);

    if (trans->position.x > screen_size.x) {
        trans->position.x = -screen_size.x;
    } else if (trans->position.x < -screen_size.x) {
        trans->position.x = screen_size.x;
    }

    if (trans->position.y > screen_size.y) {
        trans->position.y = -screen_size.y;
    } else if (trans->position.y < -screen_size.y) {
        trans->position.y = screen_size.y;
    }
}

void setup_scene() {
    create_camera_orthographic_default(&game_camera);
    game_camera.clear_color = COLOR_MAKE_BLACK();

    texture_t *ship_texture = get_texture_resource(TEXTURE_DATA_FOLDER "/player_ship.png");
    texture_t *asteroid_texture = get_texture_resource(TEXTURE_DATA_FOLDER "/asteroid.png");
    texture_t *projectile_texture = get_texture_resource(TEXTURE_DATA_FOLDER "/projectile.png");
    material_t *material = get_material_resource("data/tests/pong/pong_sprite_material.mat_def");
       
    player = &all_entities[0];
    projectiles = &all_entities[1];
    asteroids = &all_entities[MAX_PROJECTILES + 1];
    
    
    create_texture_renderer(ship_texture, material, &player->texture);
    
    for (int i = 0; i < MAX_PROJECTILES; ++i) {
        create_texture_renderer(projectile_texture, material, &projectiles[i].texture);
    }   
    
    for (int i = 0; i < MAX_ASTEROIDS; ++i) {
        create_texture_renderer(asteroid_texture, material, &asteroids[i].texture);
    }

    for (int i = 0; i < MAX_ENTITIES; ++i) {
        trans_identity(&all_entities[i].transform);
        all_entities[i].active = false;
    }
    
    player->active = true;
    used_projectiles = 0;
}

void update_entities() {
    // ========= PLAYER
    {
        direction_t direction = LEFT;
        bool rotated = false;
        if (is_key_down(KEY_A)) {
            direction = LEFT;
            rotated = true;
        } else if (is_key_down(KEY_D)) {
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
            quat_multiply(&player->transform.rotation, &rotation_quat, &player->transform.rotation);
        }

        vec3_t acceleration = VEC3_MAKE_ZERO();
        if (is_key_down(KEY_W)) {
            vec3_t up;
            trans_get_up(&player->transform, &up);
            vec3_scale(&up, PLAYER_ACCELERATION * delta_time, &acceleration);
        } else if (is_key_down(KEY_S)) {
            vec3_t down;
            trans_get_down(&player->transform, &down);
            vec3_scale(&down, (PLAYER_ACCELERATION * delta_time), &acceleration);
        } else {
            float sqrd_len = vec3_sqrd_len(&player->velocity);
            if (sqrd_len > 0) {
                vec3_t normalized_velocity;
                vec3_normalize(&player->velocity, &normalized_velocity);
                vec3_scale(&normalized_velocity, -DRAG * delta_time, &acceleration);
            }
        }

        vec3_add(&player->velocity, &acceleration, &player->velocity);

        vec3_t max_velocity = vec3_make(VELOCITY_LIMIT, VELOCITY_LIMIT, 0);
        vec3_min(&player->velocity, &max_velocity, &player->velocity);

        vec3_add(&player->transform.position, &player->velocity, &player->transform.position);
        screen_wrap(&player->transform);
        
        if (was_key_just_pressed(KEY_SPACE)) {
            printf("used: %i \n", used_projectiles);
            
            entity_t *projectile = &projectiles[used_projectiles];
            projectile->active = true;
            
            vec3_t up;
            trans_get_up(&player->transform, &up);
            vec3_scale(&up, PROJECTILE_VELOCITY, &projectile->velocity);
            vec3_add(&projectile->velocity, &player->velocity, &projectile->velocity);
            projectile->transform.rotation = player->transform.rotation;
            
            vec3_scale(&up, player->texture.size.height, &up);
            
            vec3_t offset;
            vec3_add(&player->transform.position, &up, &offset);
            projectile->transform.position = offset;
            
            used_projectiles++;
        }
    }
    
    // ============== PROJECTILES
    {
        
    }

    // ============== ASTEROIDS
    {
        
    }

    for (int i = 0; i < MAX_ENTITIES; ++i) {
        entity_t *entity = &projectiles[i];
        if (entity->active) {
            vec3_add(&entity->transform.position, &entity->velocity, &entity->transform.position);
            screen_wrap(&entity->transform);
        }
    }
}

void draw_entities() {
    for (int i = 0; i < MAX_ENTITIES; ++i) {
        entity_t *entity = &all_entities[i]; 
        if (entity->active) {
            draw_texture_renderer(&entity->texture, &entity->transform);
        }
    }
}

int main() {
    if (init_engine() != ENGINE_INIT_OK) {
        return -1;
    }
    
    setup_scene();

    do {
        start_frame();

        update_entities();

        use_camera(&game_camera);

        draw_entities();

        end_frame();
    } while (!should_quit);

    return 1;
}