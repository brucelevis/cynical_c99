//
// Created by temdisponivel on 09/06/2018.
//

#include <engine.h>
#include <resource_manager.h>
#include <input.h>
#include <stdlib.h>
#include <time.h>
#include <file.h>
#include <text.h>
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
#define POINTES_PER_ASTEROID 10

#define ASTEROID_VELOCITY .1f
#define PROJECTILE_VELOCITY .1f

#define PROJECTILE_LIFE_SPAN 5
#define ASTEROID_LIFE_SPAN 15

#define ASTEROID_SPAWN_START_INTERVAL 3

typedef struct entity {
    texture_renderer_t texture;
    transform_t transform;
    vec3_t velocity;
    bool active;
    float death_time;
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

//entity_t letter_entity;

float points;

float next_player_spawn_time;
float next_asteroid_spawn_time;

float asteroid_spawn_interval;

INLINE int get_next_active_entity_index(entity_t *entity_array, int count) {
    for (int i = 0; i < count; ++i) {
        if (!entity_array[i].active) {
            return i;
        }
    }

    return -1;
}

INLINE int get_next_projectile_index() {
    return get_next_active_entity_index(projectiles, MAX_PROJECTILES);
}

INLINE int get_next_asteroid_index() {
    return get_next_active_entity_index(asteroids, MAX_ASTEROIDS);
}

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

rect_t get_entity_rect(const entity_t *entity) {
    rect_t result;
    result.size = entity->texture.size;

    vec2_t half_size;
    vec2_scale(&entity->texture.size, -.5f, &half_size);

    vec2_t bottom_left;
    vec2_add(&entity->transform.position.xy, &half_size, &bottom_left);
    result.bottom_left = bottom_left;

    return result;
}

void reset_game() {
    for (int i = 0; i < MAX_ENTITIES; ++i) {
        trans_identity(&all_entities[i].transform);
        all_entities[i].active = false;
        vec3_set(0, 0, 0, &all_entities[i].velocity);
    }

    points = 0;
    next_player_spawn_time = current_time + 2;
    next_asteroid_spawn_time = current_time + 2;
    asteroid_spawn_interval = ASTEROID_SPAWN_START_INTERVAL;
}


texture_t *load_letter() {
    
}


void setup_scene() {
    create_camera_orthographic_default(&game_camera);
    //game_camera.clear_color = COLOR_MAKE_RED();

    texture_t *ship_texture = get_texture_resource(TEXTURE_DATA_FOLDER "/player_ship.png");
    texture_t *asteroid_texture = get_texture_resource(TEXTURE_DATA_FOLDER "/asteroid.png");
    texture_t *projectile_texture = get_texture_resource(TEXTURE_DATA_FOLDER "/projectile.png");
    material_t *material = get_material_resource("data/tests/pong/pong_sprite_material.mat_def");
    //material_t *text_renderer_material = get_material_resource("data/shaders/text_renderer.mat_def");

    player = &all_entities[0];
    projectiles = &all_entities[1];
    asteroids = &all_entities[MAX_PROJECTILES + 1];

    create_texture_renderer(ship_texture, material, &player->texture);

    /*texture_t *letter_texture = load_letter();
    create_texture_renderer(letter_texture, text_renderer_material, &letter_entity.texture);    
    trans_identity(&letter_entity.transform);*/

    for (int i = 0; i < MAX_PROJECTILES; ++i) {
        create_texture_renderer(projectile_texture, material, &projectiles[i].texture);
        trans_identity(&projectiles[i].transform);
    }

    for (int i = 0; i < MAX_ASTEROIDS; ++i) {
        create_texture_renderer(asteroid_texture, material, &asteroids[i].texture);
        trans_identity(&asteroids[i].transform);
    }

    reset_game();
}

void update_entities() {
    // ========= PLAYER
    {
        if (player->active) {
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

                int next_projectile_index = get_next_projectile_index();
                if (next_projectile_index != -1) {
                    printf("Shooting!!\n");

                    entity_t *projectile = &projectiles[next_projectile_index];
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
                    projectile->death_time = current_time + PROJECTILE_LIFE_SPAN;
                } else {
                    printf("No projectiles avaialble!\n");
                }
            }
        } else {
            if (current_time >= next_player_spawn_time) {
                player->active = true;
                trans_identity(&player->transform);
            }
        }
    }

    // ============== ASTEROIDS
    {
        if (current_time >= next_asteroid_spawn_time) {
            int index = get_next_asteroid_index();
            if (index != -1) {
                printf("Spawning asteroid!!\n");

                entity_t *asteroid = &asteroids[index];
                asteroid->active = true;
                asteroid->death_time = current_time + ASTEROID_LIFE_SPAN;

                float x = ((rand() * 2) - 1.f) * screen_size.x;
                float y = ((rand() * 2) - 1.f) * screen_size.y;
                asteroid->transform.position.xy = vec2_make(x, y);

                float random = RANDOM();
                float velocity_x = ((RANDOM() * 2) - 1.f) * ASTEROID_VELOCITY;
                float velocity_y = ((RANDOM() * 2) - 1.f) * ASTEROID_VELOCITY;
                asteroid->velocity = vec3_make(velocity_x, velocity_y, 0);

                next_asteroid_spawn_time = current_time + asteroid_spawn_interval;
                asteroid_spawn_interval *= .9f;
            } else {
                printf("No asteroids available!\n");
            }
        }

        rect_t player_rect = get_entity_rect(player);
        for (int i = 0; i < MAX_ASTEROIDS; ++i) {
            entity_t *asteroid = &asteroids[i];

            if (!asteroid->active)
                continue;

            if (current_time >= asteroid->death_time) {
                asteroid->active = false;
            } else {
                rect_t asteroid_rect = get_entity_rect(asteroid);

                if (rect_touch(&player_rect, &asteroid_rect)) {
                    printf("Player is dead!\n");
                    reset_game();
                }
            }
        }
    }

    // ============== PROJECTILES
    {
        for (int i = 0; i < MAX_PROJECTILES; ++i) {
            entity_t *projectile = &projectiles[i];

            if (!projectile->active)
                continue;

            if (current_time >= projectile->death_time) {
                projectile->active = false;
            } else {
                rect_t projectile_rect = get_entity_rect(projectile);

                for (int j = 0; j < MAX_ASTEROIDS; ++j) {
                    entity_t *asteroid = &asteroids[j];

                    if (!asteroid->active)
                        continue;

                    rect_t asteroid_rect = get_entity_rect(asteroid);

                    if (rect_touch(&projectile_rect, &asteroid_rect)) {
                        projectile->active = false;
                        asteroid->active = false;

                        points += POINTES_PER_ASTEROID;
                    }
                }
            }
        }
    }

    for (int i = 0; i < MAX_ENTITIES; ++i) {
        entity_t *entity = &all_entities[i];
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

    srand(time(null));

    setup_scene();

    do {
        start_frame();

        update_entities();

        use_camera(&game_camera);

        draw_entities();
 
        set_blend_state(true);

        //draw_texture_renderer(&letter_entity.texture, &letter_entity.transform);
        draw_string(&default_font, "the witness is the best game ever made!", VEC2_MAKE_ZERO());
        //set_blend_state(false);

        end_frame();
    } while (!should_quit);

    return 1;
}