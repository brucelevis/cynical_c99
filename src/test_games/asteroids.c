//
// Created by temdisponivel on 09/06/2018.
//

#include <engine.h>
#include <resource_manager.h>
#include <input.h>
#include "graphics.h"

#define DATA_FOLDER "data/tests/pong/"

camera_t game_camera;
camera_t game_camera_2;
texture_renderer_t texture_renderer;
transform_t texture_trans;

// TODO(temdisponivel): Move screen size, aspect ratiom view port, swapbuffers and everything non-specific-game-related to the "engine layer" insted of the "game layer"

int main() {
    if (init_engine() != ENGINE_INIT_OK) {
        return -1;
    }
    
    create_camera_orthographic_default(&game_camera);
    create_camera_orthographic_default(&game_camera_2);
    trans_identity(&texture_trans);

    texture_t *ball_texture = get_texture_resource(DATA_FOLDER "ball.png");
    material_t *material = get_material_resource("data/tests/pong/pong_sprite_material.mat_def");
    create_texture_renderer(ball_texture, material, &texture_renderer);
    
    game_camera.clear_color = COLOR_MAKE_BLUE();
    
    game_camera.view_port.size = vec2_make(.5f, .5f);
    
    game_camera_2.view_port.size = vec2_make(.5f, .5f);
    game_camera_2.view_port.bottom_left = vec2_make(0, 0);
    game_camera_2.clear_color = COLOR_MAKE_RED();
    
    do {
        start_frame();
        
        use_camera(&game_camera);
        
        draw_texture_renderer(&texture_renderer, &texture_trans);

        use_camera(&game_camera_2);

        draw_texture_renderer(&texture_renderer, &texture_trans);
        
        end_frame();
    } while (!should_quit);
    
    return 1;
}