//
// Created by temdisponivel on 09/06/2018.
//

#include <engine.h>
#include <resource_manager.h>
#include <input.h>
#include "graphics.h"

#define DATA_FOLDER "data/tests/pong/"

camera_t game_camera;
texture_renderer_t texture_renderer;
transform_t texture_trans;

// TODO(temdisponivel): Move screen size, aspect ratiom view port, swapbuffers and everything non-specific-game-related to the "engine layer" insted of the "game layer"

int main() {
    if (init_engine() != ENGINE_INIT_OK) {
        return -1;
    }
    
    create_camera_orthographic_default(&game_camera);
    trans_identity(&texture_trans);

    texture_t *ball_texture = get_texture_resource(DATA_FOLDER "ball.png");
    material_t *material = get_material_resource("data/tests/pong/pong_sprite_material.mat_def");
    create_texture_renderer(ball_texture, material, &texture_renderer);
    
    game_camera.clear_color = COLOR_MAKE_BLUE();
    
    do {
        start_frame();
        
        use_camera(&game_camera);
        
        draw_texture_renderer(&texture_renderer, &texture_trans);
        
        end_frame();
    } while (!should_quit);
    
    return 1;
}