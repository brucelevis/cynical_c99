//
// Created by temdisponivel on 02/06/2018.
//

#include "engine.h"
#include <GLFW/glfw3.h>
#include "input.h"

input_state_t current_frame = {};
input_state_t last_frame = {};

int get_glfw_key_state(key_code_t key) {
    return glfwGetKey(game_window, key);
}

key_state_t get_key_state_based_on_last_state(key_state_t last_state, int current_state) {
    if (current_state == GLFW_PRESS) {
        if (last_state == KEY_STATE_JUST_PRESSED || last_state == KEY_STATE_DOWN) {
            return KEY_STATE_DOWN;
        } else {
            return KEY_STATE_JUST_PRESSED;
        }
    } else {
        if (last_state == KEY_STATE_DOWN || last_state == KEY_STATE_JUST_PRESSED) {
            return KEY_STATE_JUST_RELEASED;
        } else {
            return KEY_STATE_NORMAL;
        }
    }
}

void update_input_state(input_state_t *last_input, input_state_t *input) {
    input->key_space = get_key_state_based_on_last_state(last_input->key_space, get_glfw_key_state(KEY_SPACE));
    input->key_apostrophe = get_key_state_based_on_last_state(last_input->key_apostrophe, get_glfw_key_state(KEY_APOSTROPHE));
    input->key_comma = get_key_state_based_on_last_state(last_input->key_comma, get_glfw_key_state(KEY_COMMA));
    input->key_minus = get_key_state_based_on_last_state(last_input->key_minus, get_glfw_key_state(KEY_MINUS));
    input->key_period = get_key_state_based_on_last_state(last_input->key_period, get_glfw_key_state(KEY_PERIOD));
    input->key_slash = get_key_state_based_on_last_state(last_input->key_slash, get_glfw_key_state(KEY_SLASH));
    input->key_0 = get_key_state_based_on_last_state(last_input->key_0, get_glfw_key_state(KEY_0));
    input->key_1 = get_key_state_based_on_last_state(last_input->key_1, get_glfw_key_state(KEY_1));
    input->key_2 = get_key_state_based_on_last_state(last_input->key_2, get_glfw_key_state(KEY_2));
    input->key_3 = get_key_state_based_on_last_state(last_input->key_3, get_glfw_key_state(KEY_3));
    input->key_4 = get_key_state_based_on_last_state(last_input->key_4, get_glfw_key_state(KEY_4));
    input->key_5 = get_key_state_based_on_last_state(last_input->key_5, get_glfw_key_state(KEY_5));
    input->key_6 = get_key_state_based_on_last_state(last_input->key_6, get_glfw_key_state(KEY_6));
    input->key_7 = get_key_state_based_on_last_state(last_input->key_7, get_glfw_key_state(KEY_7));
    input->key_8 = get_key_state_based_on_last_state(last_input->key_8, get_glfw_key_state(KEY_8));
    input->key_9 = get_key_state_based_on_last_state(last_input->key_9, get_glfw_key_state(KEY_9));
    input->key_semicolon = get_key_state_based_on_last_state(last_input->key_semicolon, get_glfw_key_state(KEY_SEMICOLON));
    input->key_equal = get_key_state_based_on_last_state(last_input->key_equal, get_glfw_key_state(KEY_EQUAL));
    input->key_a = get_key_state_based_on_last_state(last_input->key_a, get_glfw_key_state(KEY_A));
    input->key_b = get_key_state_based_on_last_state(last_input->key_b, get_glfw_key_state(KEY_B));
    input->key_c = get_key_state_based_on_last_state(last_input->key_c, get_glfw_key_state(KEY_C));
    input->key_d = get_key_state_based_on_last_state(last_input->key_d, get_glfw_key_state(KEY_D));
    input->key_e = get_key_state_based_on_last_state(last_input->key_e, get_glfw_key_state(KEY_E));
    input->key_f = get_key_state_based_on_last_state(last_input->key_f, get_glfw_key_state(KEY_F));
    input->key_g = get_key_state_based_on_last_state(last_input->key_g, get_glfw_key_state(KEY_G));
    input->key_h = get_key_state_based_on_last_state(last_input->key_h, get_glfw_key_state(KEY_H));
    input->key_i = get_key_state_based_on_last_state(last_input->key_i, get_glfw_key_state(KEY_I));
    input->key_j = get_key_state_based_on_last_state(last_input->key_j, get_glfw_key_state(KEY_J));
    input->key_k = get_key_state_based_on_last_state(last_input->key_k, get_glfw_key_state(KEY_K));
    input->key_l = get_key_state_based_on_last_state(last_input->key_l, get_glfw_key_state(KEY_L));
    input->key_m = get_key_state_based_on_last_state(last_input->key_m, get_glfw_key_state(KEY_M));
    input->key_n = get_key_state_based_on_last_state(last_input->key_n, get_glfw_key_state(KEY_N));
    input->key_o = get_key_state_based_on_last_state(last_input->key_o, get_glfw_key_state(KEY_O));
    input->key_p = get_key_state_based_on_last_state(last_input->key_p, get_glfw_key_state(KEY_P));
    input->key_q = get_key_state_based_on_last_state(last_input->key_q, get_glfw_key_state(KEY_Q));
    input->key_r = get_key_state_based_on_last_state(last_input->key_r, get_glfw_key_state(KEY_R));
    input->key_s = get_key_state_based_on_last_state(last_input->key_s, get_glfw_key_state(KEY_S));
    input->key_t = get_key_state_based_on_last_state(last_input->key_t, get_glfw_key_state(KEY_T));
    input->key_u = get_key_state_based_on_last_state(last_input->key_u, get_glfw_key_state(KEY_U));
    input->key_v = get_key_state_based_on_last_state(last_input->key_v, get_glfw_key_state(KEY_V));
    input->key_w = get_key_state_based_on_last_state(last_input->key_w, get_glfw_key_state(KEY_W));
    input->key_x = get_key_state_based_on_last_state(last_input->key_x, get_glfw_key_state(KEY_X));
    input->key_y = get_key_state_based_on_last_state(last_input->key_y, get_glfw_key_state(KEY_Y));
    input->key_z = get_key_state_based_on_last_state(last_input->key_z, get_glfw_key_state(KEY_Z));
    input->key_left_bracket = get_key_state_based_on_last_state(last_input->key_left_bracket, get_glfw_key_state(KEY_LEFT_BRACKET));
    input->key_backslash = get_key_state_based_on_last_state(last_input->key_backslash, get_glfw_key_state(KEY_BACKSLASH));
    input->key_right_bracket = get_key_state_based_on_last_state(last_input->key_right_bracket, get_glfw_key_state(KEY_RIGHT_BRACKET));
    input->key_grave_accent = get_key_state_based_on_last_state(last_input->key_grave_accent, get_glfw_key_state(KEY_GRAVE_ACCENT));
    input->key_world_1 = get_key_state_based_on_last_state(last_input->key_world_1, get_glfw_key_state(KEY_WORLD_1));
    input->key_world_2 = get_key_state_based_on_last_state(last_input->key_world_2, get_glfw_key_state(KEY_WORLD_2));
    input->key_escape = get_key_state_based_on_last_state(last_input->key_escape, get_glfw_key_state(KEY_ESCAPE));
    input->key_enter = get_key_state_based_on_last_state(last_input->key_enter, get_glfw_key_state(KEY_ENTER));
    input->key_tab = get_key_state_based_on_last_state(last_input->key_tab, get_glfw_key_state(KEY_TAB));
    input->key_backspace = get_key_state_based_on_last_state(last_input->key_backspace, get_glfw_key_state(KEY_BACKSPACE));
    input->key_insert = get_key_state_based_on_last_state(last_input->key_insert, get_glfw_key_state(KEY_INSERT));
    input->key_delete = get_key_state_based_on_last_state(last_input->key_delete, get_glfw_key_state(KEY_DELETE));
    input->key_right = get_key_state_based_on_last_state(last_input->key_right, get_glfw_key_state(KEY_RIGHT));
    input->key_left = get_key_state_based_on_last_state(last_input->key_left, get_glfw_key_state(KEY_LEFT));
    input->key_down = get_key_state_based_on_last_state(last_input->key_down, get_glfw_key_state(KEY_DOWN));
    input->key_up = get_key_state_based_on_last_state(last_input->key_up, get_glfw_key_state(KEY_UP));
    input->key_page_up = get_key_state_based_on_last_state(last_input->key_page_up, get_glfw_key_state(KEY_PAGE_UP));
    input->key_page_down = get_key_state_based_on_last_state(last_input->key_page_down, get_glfw_key_state(KEY_PAGE_DOWN));
    input->key_home = get_key_state_based_on_last_state(last_input->key_home, get_glfw_key_state(KEY_HOME));
    input->key_end = get_key_state_based_on_last_state(last_input->key_end, get_glfw_key_state(KEY_END));
    input->key_caps_lock = get_key_state_based_on_last_state(last_input->key_caps_lock, get_glfw_key_state(KEY_CAPS_LOCK));
    input->key_scroll_lock = get_key_state_based_on_last_state(last_input->key_scroll_lock, get_glfw_key_state(KEY_SCROLL_LOCK));
    input->key_num_lock = get_key_state_based_on_last_state(last_input->key_num_lock, get_glfw_key_state(KEY_NUM_LOCK));
    input->key_print_screen = get_key_state_based_on_last_state(last_input->key_print_screen, get_glfw_key_state(KEY_PRINT_SCREEN));
    input->key_pause = get_key_state_based_on_last_state(last_input->key_pause, get_glfw_key_state(KEY_PAUSE));
    input->key_f1 = get_key_state_based_on_last_state(last_input->key_f1, get_glfw_key_state(KEY_F1));
    input->key_f2 = get_key_state_based_on_last_state(last_input->key_f2, get_glfw_key_state(KEY_F2));
    input->key_f3 = get_key_state_based_on_last_state(last_input->key_f3, get_glfw_key_state(KEY_F3));
    input->key_f4 = get_key_state_based_on_last_state(last_input->key_f4, get_glfw_key_state(KEY_F4));
    input->key_f5 = get_key_state_based_on_last_state(last_input->key_f5, get_glfw_key_state(KEY_F5));
    input->key_f6 = get_key_state_based_on_last_state(last_input->key_f6, get_glfw_key_state(KEY_F6));
    input->key_f7 = get_key_state_based_on_last_state(last_input->key_f7, get_glfw_key_state(KEY_F7));
    input->key_f8 = get_key_state_based_on_last_state(last_input->key_f8, get_glfw_key_state(KEY_F8));
    input->key_f9 = get_key_state_based_on_last_state(last_input->key_f9, get_glfw_key_state(KEY_F9));
    input->key_f10 = get_key_state_based_on_last_state(last_input->key_f10, get_glfw_key_state(KEY_F10));
    input->key_f11 = get_key_state_based_on_last_state(last_input->key_f11, get_glfw_key_state(KEY_F11));
    input->key_f12 = get_key_state_based_on_last_state(last_input->key_f12, get_glfw_key_state(KEY_F12));
    input->key_f13 = get_key_state_based_on_last_state(last_input->key_f13, get_glfw_key_state(KEY_F13));
    input->key_f14 = get_key_state_based_on_last_state(last_input->key_f14, get_glfw_key_state(KEY_F14));
    input->key_f15 = get_key_state_based_on_last_state(last_input->key_f15, get_glfw_key_state(KEY_F15));
    input->key_f16 = get_key_state_based_on_last_state(last_input->key_f16, get_glfw_key_state(KEY_F16));
    input->key_f17 = get_key_state_based_on_last_state(last_input->key_f17, get_glfw_key_state(KEY_F17));
    input->key_f18 = get_key_state_based_on_last_state(last_input->key_f18, get_glfw_key_state(KEY_F18));
    input->key_f19 = get_key_state_based_on_last_state(last_input->key_f19, get_glfw_key_state(KEY_F19));
    input->key_f20 = get_key_state_based_on_last_state(last_input->key_f20, get_glfw_key_state(KEY_F20));
    input->key_f21 = get_key_state_based_on_last_state(last_input->key_f21, get_glfw_key_state(KEY_F21));
    input->key_f22 = get_key_state_based_on_last_state(last_input->key_f22, get_glfw_key_state(KEY_F22));
    input->key_f23 = get_key_state_based_on_last_state(last_input->key_f23, get_glfw_key_state(KEY_F23));
    input->key_f24 = get_key_state_based_on_last_state(last_input->key_f24, get_glfw_key_state(KEY_F24));
    input->key_f25 = get_key_state_based_on_last_state(last_input->key_f25, get_glfw_key_state(KEY_F25));
    input->key_kp_0 = get_key_state_based_on_last_state(last_input->key_kp_0, get_glfw_key_state(KEY_KP_0));
    input->key_kp_1 = get_key_state_based_on_last_state(last_input->key_kp_1, get_glfw_key_state(KEY_KP_1));
    input->key_kp_2 = get_key_state_based_on_last_state(last_input->key_kp_2, get_glfw_key_state(KEY_KP_2));
    input->key_kp_3 = get_key_state_based_on_last_state(last_input->key_kp_3, get_glfw_key_state(KEY_KP_3));
    input->key_kp_4 = get_key_state_based_on_last_state(last_input->key_kp_4, get_glfw_key_state(KEY_KP_4));
    input->key_kp_5 = get_key_state_based_on_last_state(last_input->key_kp_5, get_glfw_key_state(KEY_KP_5));
    input->key_kp_6 = get_key_state_based_on_last_state(last_input->key_kp_6, get_glfw_key_state(KEY_KP_6));
    input->key_kp_7 = get_key_state_based_on_last_state(last_input->key_kp_7, get_glfw_key_state(KEY_KP_7));
    input->key_kp_8 = get_key_state_based_on_last_state(last_input->key_kp_8, get_glfw_key_state(KEY_KP_8));
    input->key_kp_9 = get_key_state_based_on_last_state(last_input->key_kp_9, get_glfw_key_state(KEY_KP_9));
    input->key_kp_decimal = get_key_state_based_on_last_state(last_input->key_kp_decimal, get_glfw_key_state(KEY_KP_DECIMAL));
    input->key_kp_divide = get_key_state_based_on_last_state(last_input->key_kp_divide, get_glfw_key_state(KEY_KP_DIVIDE));
    input->key_kp_multiply = get_key_state_based_on_last_state(last_input->key_kp_multiply, get_glfw_key_state(KEY_KP_MULTIPLY));
    input->key_kp_subtract = get_key_state_based_on_last_state(last_input->key_kp_subtract, get_glfw_key_state(KEY_KP_SUBTRACT));
    input->key_kp_add = get_key_state_based_on_last_state(last_input->key_kp_add, get_glfw_key_state(KEY_KP_ADD));
    input->key_kp_enter = get_key_state_based_on_last_state(last_input->key_kp_enter, get_glfw_key_state(KEY_KP_ENTER));
    input->key_kp_equal = get_key_state_based_on_last_state(last_input->key_kp_equal, get_glfw_key_state(KEY_KP_EQUAL));
    input->key_left_shift = get_key_state_based_on_last_state(last_input->key_left_shift, get_glfw_key_state(KEY_LEFT_SHIFT));
    input->key_left_control = get_key_state_based_on_last_state(last_input->key_left_control, get_glfw_key_state(KEY_LEFT_CONTROL));
    input->key_left_alt = get_key_state_based_on_last_state(last_input->key_left_alt, get_glfw_key_state(KEY_LEFT_ALT));
    input->key_left_super = get_key_state_based_on_last_state(last_input->key_left_super, get_glfw_key_state(KEY_LEFT_SUPER));
    input->key_right_shift = get_key_state_based_on_last_state(last_input->key_right_shift, get_glfw_key_state(KEY_RIGHT_SHIFT));
    input->key_right_control = get_key_state_based_on_last_state(last_input->key_right_control, get_glfw_key_state(KEY_RIGHT_CONTROL));
    input->key_right_alt = get_key_state_based_on_last_state(last_input->key_right_alt, get_glfw_key_state(KEY_RIGHT_ALT));
    input->key_right_super = get_key_state_based_on_last_state(last_input->key_right_super, get_glfw_key_state(KEY_RIGHT_SUPER));
    input->key_menu = get_key_state_based_on_last_state(last_input->key_menu, get_glfw_key_state(KEY_MENU));
}

void update_input() {
    glfwPollEvents();
    
    last_frame = current_frame;
    update_input_state(&last_frame, &current_frame);
}

key_state_t get_key_state(key_code_t key) {
    if (key == KEY_SPACE) {
        return current_frame.key_space;
    } else if (key == KEY_APOSTROPHE) {
        return current_frame.key_apostrophe;
    } else if (key == KEY_COMMA) {
        return current_frame.key_comma;
    } else if (key == KEY_MINUS) {
        return current_frame.key_minus;
    } else if (key == KEY_PERIOD) {
        return current_frame.key_period;
    } else if (key == KEY_SLASH) {
        return current_frame.key_slash;
    } else if (key == KEY_0) {
        return current_frame.key_0;
    } else if (key == KEY_1) {
        return current_frame.key_1;
    } else if (key == KEY_2) {
        return current_frame.key_2;
    } else if (key == KEY_3) {
        return current_frame.key_3;
    } else if (key == KEY_4) {
        return current_frame.key_4;
    } else if (key == KEY_5) {
        return current_frame.key_5;
    } else if (key == KEY_6) {
        return current_frame.key_6;
    } else if (key == KEY_7) {
        return current_frame.key_7;
    } else if (key == KEY_8) {
        return current_frame.key_8;
    } else if (key == KEY_9) {
        return current_frame.key_9;
    } else if (key == KEY_SEMICOLON) {
        return current_frame.key_semicolon;
    } else if (key == KEY_EQUAL) {
        return current_frame.key_equal;
    } else if (key == KEY_A) {
        return current_frame.key_a;
    } else if (key == KEY_B) {
        return current_frame.key_b;
    } else if (key == KEY_C) {
        return current_frame.key_c;
    } else if (key == KEY_D) {
        return current_frame.key_d;
    } else if (key == KEY_E) {
        return current_frame.key_e;
    } else if (key == KEY_F) {
        return current_frame.key_f;
    } else if (key == KEY_G) {
        return current_frame.key_g;
    } else if (key == KEY_H) {
        return current_frame.key_h;
    } else if (key == KEY_I) {
        return current_frame.key_i;
    } else if (key == KEY_J) {
        return current_frame.key_j;
    } else if (key == KEY_K) {
        return current_frame.key_k;
    } else if (key == KEY_L) {
        return current_frame.key_l;
    } else if (key == KEY_M) {
        return current_frame.key_m;
    } else if (key == KEY_N) {
        return current_frame.key_n;
    } else if (key == KEY_O) {
        return current_frame.key_o;
    } else if (key == KEY_P) {
        return current_frame.key_p;
    } else if (key == KEY_Q) {
        return current_frame.key_q;
    } else if (key == KEY_R) {
        return current_frame.key_r;
    } else if (key == KEY_S) {
        return current_frame.key_s;
    } else if (key == KEY_T) {
        return current_frame.key_t;
    } else if (key == KEY_U) {
        return current_frame.key_u;
    } else if (key == KEY_V) {
        return current_frame.key_v;
    } else if (key == KEY_W) {
        return current_frame.key_w;
    } else if (key == KEY_X) {
        return current_frame.key_x;
    } else if (key == KEY_Y) {
        return current_frame.key_y;
    } else if (key == KEY_Z) {
        return current_frame.key_z;
    } else if (key == KEY_LEFT_BRACKET) {
        return current_frame.key_left_bracket;
    } else if (key == KEY_BACKSLASH) {
        return current_frame.key_backslash;
    } else if (key == KEY_RIGHT_BRACKET) {
        return current_frame.key_right_bracket;
    } else if (key == KEY_GRAVE_ACCENT) {
        return current_frame.key_grave_accent;
    } else if (key == KEY_WORLD_1) {
        return current_frame.key_world_1;
    } else if (key == KEY_WORLD_2) {
        return current_frame.key_world_2;
    } else if (key == KEY_ESCAPE) {
        return current_frame.key_escape;
    } else if (key == KEY_ENTER) {
        return current_frame.key_enter;
    } else if (key == KEY_TAB) {
        return current_frame.key_tab;
    } else if (key == KEY_BACKSPACE) {
        return current_frame.key_backspace;
    } else if (key == KEY_INSERT) {
        return current_frame.key_insert;
    } else if (key == KEY_DELETE) {
        return current_frame.key_delete;
    } else if (key == KEY_RIGHT) {
        return current_frame.key_right;
    } else if (key == KEY_LEFT) {
        return current_frame.key_left;
    } else if (key == KEY_DOWN) {
        return current_frame.key_down;
    } else if (key == KEY_UP) {
        return current_frame.key_up;
    } else if (key == KEY_PAGE_UP) {
        return current_frame.key_page_up;
    } else if (key == KEY_PAGE_DOWN) {
        return current_frame.key_page_down;
    } else if (key == KEY_HOME) {
        return current_frame.key_home;
    } else if (key == KEY_END) {
        return current_frame.key_end;
    } else if (key == KEY_CAPS_LOCK) {
        return current_frame.key_caps_lock;
    } else if (key == KEY_SCROLL_LOCK) {
        return current_frame.key_scroll_lock;
    } else if (key == KEY_NUM_LOCK) {
        return current_frame.key_num_lock;
    } else if (key == KEY_PRINT_SCREEN) {
        return current_frame.key_print_screen;
    } else if (key == KEY_PAUSE) {
        return current_frame.key_pause;
    } else if (key == KEY_F1) {
        return current_frame.key_f1;
    } else if (key == KEY_F2) {
        return current_frame.key_f2;
    } else if (key == KEY_F3) {
        return current_frame.key_f3;
    } else if (key == KEY_F4) {
        return current_frame.key_f4;
    } else if (key == KEY_F5) {
        return current_frame.key_f5;
    } else if (key == KEY_F6) {
        return current_frame.key_f6;
    } else if (key == KEY_F7) {
        return current_frame.key_f7;
    } else if (key == KEY_F8) {
        return current_frame.key_f8;
    } else if (key == KEY_F9) {
        return current_frame.key_f9;
    } else if (key == KEY_F10) {
        return current_frame.key_f10;
    } else if (key == KEY_F11) {
        return current_frame.key_f11;
    } else if (key == KEY_F12) {
        return current_frame.key_f12;
    } else if (key == KEY_F13) {
        return current_frame.key_f13;
    } else if (key == KEY_F14) {
        return current_frame.key_f14;
    } else if (key == KEY_F15) {
        return current_frame.key_f15;
    } else if (key == KEY_F16) {
        return current_frame.key_f16;
    } else if (key == KEY_F17) {
        return current_frame.key_f17;
    } else if (key == KEY_F18) {
        return current_frame.key_f18;
    } else if (key == KEY_F19) {
        return current_frame.key_f19;
    } else if (key == KEY_F20) {
        return current_frame.key_f20;
    } else if (key == KEY_F21) {
        return current_frame.key_f21;
    } else if (key == KEY_F22) {
        return current_frame.key_f22;
    } else if (key == KEY_F23) {
        return current_frame.key_f23;
    } else if (key == KEY_F24) {
        return current_frame.key_f24;
    } else if (key == KEY_F25) {
        return current_frame.key_f25;
    } else if (key == KEY_KP_0) {
        return current_frame.key_kp_0;
    } else if (key == KEY_KP_1) {
        return current_frame.key_kp_1;
    } else if (key == KEY_KP_2) {
        return current_frame.key_kp_2;
    } else if (key == KEY_KP_3) {
        return current_frame.key_kp_3;
    } else if (key == KEY_KP_4) {
        return current_frame.key_kp_4;
    } else if (key == KEY_KP_5) {
        return current_frame.key_kp_5;
    } else if (key == KEY_KP_6) {
        return current_frame.key_kp_6;
    } else if (key == KEY_KP_7) {
        return current_frame.key_kp_7;
    } else if (key == KEY_KP_8) {
        return current_frame.key_kp_8;
    } else if (key == KEY_KP_9) {
        return current_frame.key_kp_9;
    } else if (key == KEY_KP_DECIMAL) {
        return current_frame.key_kp_decimal;
    } else if (key == KEY_KP_DIVIDE) {
        return current_frame.key_kp_divide;
    } else if (key == KEY_KP_MULTIPLY) {
        return current_frame.key_kp_multiply;
    } else if (key == KEY_KP_SUBTRACT) {
        return current_frame.key_kp_subtract;
    } else if (key == KEY_KP_ADD) {
        return current_frame.key_kp_add;
    } else if (key == KEY_KP_ENTER) {
        return current_frame.key_kp_enter;
    } else if (key == KEY_KP_EQUAL) {
        return current_frame.key_kp_equal;
    } else if (key == KEY_LEFT_SHIFT) {
        return current_frame.key_left_shift;
    } else if (key == KEY_LEFT_CONTROL) {
        return current_frame.key_left_control;
    } else if (key == KEY_LEFT_ALT) {
        return current_frame.key_left_alt;
    } else if (key == KEY_LEFT_SUPER) {
        return current_frame.key_left_super;
    } else if (key == KEY_RIGHT_SHIFT) {
        return current_frame.key_right_shift;
    } else if (key == KEY_RIGHT_CONTROL) {
        return current_frame.key_right_control;
    } else if (key == KEY_RIGHT_ALT) {
        return current_frame.key_right_alt;
    } else if (key == KEY_RIGHT_SUPER) {
        return current_frame.key_right_super;
    } else if (key == KEY_MENU) {
        return current_frame.key_menu;
    } else {
        return KEY_STATE_NORMAL;
    }
}

bool was_key_just_pressed(key_code_t key) {
    key_state_t state = get_key_state(key);
    return state == KEY_STATE_JUST_PRESSED;
}

bool was_key_just_released(key_code_t key) {
    key_state_t state = get_key_state(key);
    return state == KEY_STATE_JUST_RELEASED;
}

bool is_key_down(key_code_t key) {
    key_state_t state = get_key_state(key);
    return state == KEY_STATE_DOWN;
}

bool is_key_up(key_code_t key) {
    key_state_t state = get_key_state(key);
    return state == KEY_STATE_NORMAL;
}