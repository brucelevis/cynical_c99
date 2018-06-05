//
// Created by temdisponivel on 02/06/2018.
//

#include <GLFW/glfw3.h>
#include "input.h"

// TODO(temdisponivel): get this from a better way
extern GLFWwindow *game_window;

input_state_t current_frame;
input_state_t last_frame;

key_state_t get_glfw_key_state(key_code_t key) {
    int state = glfwGetKey(game_window, key);
    if (state == GLFW_PRESS) {
        return KEY_STATE_DOWN;
    } else if (state == GLFW_RELEASE) {
        return KEY_STATE_UP;
    } else {
        return KEY_STATE_NORMAL;
    }
}

key_state_t get_key_state_based_on_last_state(key_state_t last_state, key_state_t current_state) {
    if (current_state == KEY_STATE_DOWN) {
        return KEY_STATE_DOWN;
    } else if (current_state == KEY_STATE_UP) {
        return KEY_STATE_UP;
    }

    if (last_state == KEY_STATE_UP) {
        return KEY_STATE_NORMAL;
    } else if (last_state == KEY_STATE_DOWN || last_state == KEY_STATE_PRESSED) {
        return KEY_STATE_PRESSED;
    } else {
        return KEY_STATE_NORMAL;
    }
}

void update_input_state(input_state_t *input) {
    input->key_space = get_glfw_key_state(KEY_SPACE);
    input->key_apostrophe = get_glfw_key_state(KEY_APOSTROPHE);
    input->key_comma = get_glfw_key_state(KEY_COMMA);
    input->key_minus = get_glfw_key_state(KEY_MINUS);
    input->key_period = get_glfw_key_state(KEY_PERIOD);
    input->key_slash = get_glfw_key_state(KEY_SLASH);
    input->key_0 = get_glfw_key_state(KEY_0);
    input->key_1 = get_glfw_key_state(KEY_1);
    input->key_2 = get_glfw_key_state(KEY_2);
    input->key_3 = get_glfw_key_state(KEY_3);
    input->key_4 = get_glfw_key_state(KEY_4);
    input->key_5 = get_glfw_key_state(KEY_5);
    input->key_6 = get_glfw_key_state(KEY_6);
    input->key_7 = get_glfw_key_state(KEY_7);
    input->key_8 = get_glfw_key_state(KEY_8);
    input->key_9 = get_glfw_key_state(KEY_9);
    input->key_semicolon = get_glfw_key_state(KEY_SEMICOLON);
    input->key_equal = get_glfw_key_state(KEY_EQUAL);
    input->key_a = get_glfw_key_state(KEY_A);
    input->key_b = get_glfw_key_state(KEY_B);
    input->key_c = get_glfw_key_state(KEY_C);
    input->key_d = get_glfw_key_state(KEY_D);
    input->key_e = get_glfw_key_state(KEY_E);
    input->key_f = get_glfw_key_state(KEY_F);
    input->key_g = get_glfw_key_state(KEY_G);
    input->key_h = get_glfw_key_state(KEY_H);
    input->key_i = get_glfw_key_state(KEY_I);
    input->key_j = get_glfw_key_state(KEY_J);
    input->key_k = get_glfw_key_state(KEY_K);
    input->key_l = get_glfw_key_state(KEY_L);
    input->key_m = get_glfw_key_state(KEY_M);
    input->key_n = get_glfw_key_state(KEY_N);
    input->key_o = get_glfw_key_state(KEY_O);
    input->key_p = get_glfw_key_state(KEY_P);
    input->key_q = get_glfw_key_state(KEY_Q);
    input->key_r = get_glfw_key_state(KEY_R);
    input->key_s = get_glfw_key_state(KEY_S);
    input->key_t = get_glfw_key_state(KEY_T);
    input->key_u = get_glfw_key_state(KEY_U);
    input->key_v = get_glfw_key_state(KEY_V);
    input->key_w = get_glfw_key_state(KEY_W);
    input->key_x = get_glfw_key_state(KEY_X);
    input->key_y = get_glfw_key_state(KEY_Y);
    input->key_z = get_glfw_key_state(KEY_Z);
    input->key_left_bracket = get_glfw_key_state(KEY_LEFT_BRACKET);
    input->key_backslash = get_glfw_key_state(KEY_BACKSLASH);
    input->key_right_bracket = get_glfw_key_state(KEY_RIGHT_BRACKET);
    input->key_grave_accent = get_glfw_key_state(KEY_GRAVE_ACCENT);
    input->key_world_1 = get_glfw_key_state(KEY_WORLD_1);
    input->key_world_2 = get_glfw_key_state(KEY_WORLD_2);

    input->key_escape = get_glfw_key_state(KEY_ESCAPE);
    input->key_enter = get_glfw_key_state(KEY_ENTER);
    input->key_tab = get_glfw_key_state(KEY_TAB);
    input->key_backspace = get_glfw_key_state(KEY_BACKSPACE);
    input->key_insert = get_glfw_key_state(KEY_INSERT);
    input->key_delete = get_glfw_key_state(KEY_DELETE);
    input->key_right = get_glfw_key_state(KEY_RIGHT);
    input->key_left = get_glfw_key_state(KEY_LEFT);
    input->key_down = get_glfw_key_state(KEY_DOWN);
    input->key_up = get_glfw_key_state(KEY_UP);
    input->key_page_up = get_glfw_key_state(KEY_PAGE_UP);
    input->key_page_down = get_glfw_key_state(KEY_PAGE_DOWN);
    input->key_home = get_glfw_key_state(KEY_HOME);
    input->key_end = get_glfw_key_state(KEY_END);
    input->key_caps_lock = get_glfw_key_state(KEY_CAPS_LOCK);
    input->key_scroll_lock = get_glfw_key_state(KEY_SCROLL_LOCK);
    input->key_num_lock = get_glfw_key_state(KEY_NUM_LOCK);
    input->key_print_screen = get_glfw_key_state(KEY_PRINT_SCREEN);
    input->key_pause = get_glfw_key_state(KEY_PAUSE);
    input->key_f1 = get_glfw_key_state(KEY_F1);
    input->key_f2 = get_glfw_key_state(KEY_F2);
    input->key_f3 = get_glfw_key_state(KEY_F3);
    input->key_f4 = get_glfw_key_state(KEY_F4);
    input->key_f5 = get_glfw_key_state(KEY_F5);
    input->key_f6 = get_glfw_key_state(KEY_F6);
    input->key_f7 = get_glfw_key_state(KEY_F7);
    input->key_f8 = get_glfw_key_state(KEY_F8);
    input->key_f9 = get_glfw_key_state(KEY_F9);
    input->key_f10 = get_glfw_key_state(KEY_F10);
    input->key_f11 = get_glfw_key_state(KEY_F11);
    input->key_f12 = get_glfw_key_state(KEY_F12);
    input->key_f13 = get_glfw_key_state(KEY_F13);
    input->key_f14 = get_glfw_key_state(KEY_F14);
    input->key_f15 = get_glfw_key_state(KEY_F15);
    input->key_f16 = get_glfw_key_state(KEY_F16);
    input->key_f17 = get_glfw_key_state(KEY_F17);
    input->key_f18 = get_glfw_key_state(KEY_F18);
    input->key_f19 = get_glfw_key_state(KEY_F19);
    input->key_f20 = get_glfw_key_state(KEY_F20);
    input->key_f21 = get_glfw_key_state(KEY_F21);
    input->key_f22 = get_glfw_key_state(KEY_F22);
    input->key_f23 = get_glfw_key_state(KEY_F23);
    input->key_f24 = get_glfw_key_state(KEY_F24);
    input->key_f25 = get_glfw_key_state(KEY_F25);
    input->key_kp_0 = get_glfw_key_state(KEY_KP_0);
    input->key_kp_1 = get_glfw_key_state(KEY_KP_1);
    input->key_kp_2 = get_glfw_key_state(KEY_KP_2);
    input->key_kp_3 = get_glfw_key_state(KEY_KP_3);
    input->key_kp_4 = get_glfw_key_state(KEY_KP_4);
    input->key_kp_5 = get_glfw_key_state(KEY_KP_5);
    input->key_kp_6 = get_glfw_key_state(KEY_KP_6);
    input->key_kp_7 = get_glfw_key_state(KEY_KP_7);
    input->key_kp_8 = get_glfw_key_state(KEY_KP_8);
    input->key_kp_9 = get_glfw_key_state(KEY_KP_9);
    input->key_kp_decimal = get_glfw_key_state(KEY_KP_DECIMAL);
    input->key_kp_divide = get_glfw_key_state(KEY_KP_DIVIDE);
    input->key_kp_multiply = get_glfw_key_state(KEY_KP_MULTIPLY);
    input->key_kp_subtract = get_glfw_key_state(KEY_KP_SUBTRACT);
    input->key_kp_add = get_glfw_key_state(KEY_KP_ADD);
    input->key_kp_enter = get_glfw_key_state(KEY_KP_ENTER);
    input->key_kp_equal = get_glfw_key_state(KEY_KP_EQUAL);
    input->key_left_shift = get_glfw_key_state(KEY_LEFT_SHIFT);
    input->key_left_control = get_glfw_key_state(KEY_LEFT_CONTROL);
    input->key_left_alt = get_glfw_key_state(KEY_LEFT_ALT);
    input->key_left_super = get_glfw_key_state(KEY_LEFT_SUPER);
    input->key_right_shift = get_glfw_key_state(KEY_RIGHT_SHIFT);
    input->key_right_control = get_glfw_key_state(KEY_RIGHT_CONTROL);
    input->key_right_alt = get_glfw_key_state(KEY_RIGHT_ALT);
    input->key_right_super = get_glfw_key_state(KEY_RIGHT_SUPER);
    input->key_menu = get_glfw_key_state(KEY_MENU);
}

void update_input_based_on_last_frame(input_state_t *last_frame, const input_state_t *current_frame,
                                      input_state_t *dest) {
    dest->key_space = get_key_state_based_on_last_state(last_frame->key_space, current_frame->key_space);

    dest->key_apostrophe = get_key_state_based_on_last_state(last_frame->key_apostrophe,
                                                             current_frame->key_apostrophe);

    dest->key_comma = get_key_state_based_on_last_state(last_frame->key_comma, current_frame->key_comma);

    dest->key_minus = get_key_state_based_on_last_state(last_frame->key_minus, current_frame->key_minus);

    dest->key_period = get_key_state_based_on_last_state(last_frame->key_period, current_frame->key_period);

    dest->key_slash = get_key_state_based_on_last_state(last_frame->key_slash, current_frame->key_slash);

    dest->key_0 = get_key_state_based_on_last_state(last_frame->key_0, current_frame->key_0);

    dest->key_1 = get_key_state_based_on_last_state(last_frame->key_1, current_frame->key_1);

    dest->key_2 = get_key_state_based_on_last_state(last_frame->key_2, current_frame->key_2);

    dest->key_3 = get_key_state_based_on_last_state(last_frame->key_3, current_frame->key_3);

    dest->key_4 = get_key_state_based_on_last_state(last_frame->key_4, current_frame->key_4);

    dest->key_5 = get_key_state_based_on_last_state(last_frame->key_5, current_frame->key_5);

    dest->key_6 = get_key_state_based_on_last_state(last_frame->key_6, current_frame->key_6);

    dest->key_7 = get_key_state_based_on_last_state(last_frame->key_7, current_frame->key_7);

    dest->key_8 = get_key_state_based_on_last_state(last_frame->key_8, current_frame->key_8);

    dest->key_9 = get_key_state_based_on_last_state(last_frame->key_9, current_frame->key_9);

    dest->key_semicolon = get_key_state_based_on_last_state(last_frame->key_semicolon, current_frame->key_semicolon);

    dest->key_equal = get_key_state_based_on_last_state(last_frame->key_equal, current_frame->key_equal);

    dest->key_a = get_key_state_based_on_last_state(last_frame->key_a, current_frame->key_a);

    dest->key_b = get_key_state_based_on_last_state(last_frame->key_b, current_frame->key_b);

    dest->key_c = get_key_state_based_on_last_state(last_frame->key_c, current_frame->key_c);

    dest->key_d = get_key_state_based_on_last_state(last_frame->key_d, current_frame->key_d);

    dest->key_e = get_key_state_based_on_last_state(last_frame->key_e, current_frame->key_e);

    dest->key_f = get_key_state_based_on_last_state(last_frame->key_f, current_frame->key_f);

    dest->key_g = get_key_state_based_on_last_state(last_frame->key_g, current_frame->key_g);

    dest->key_h = get_key_state_based_on_last_state(last_frame->key_h, current_frame->key_h);

    dest->key_i = get_key_state_based_on_last_state(last_frame->key_i, current_frame->key_i);

    dest->key_j = get_key_state_based_on_last_state(last_frame->key_j, current_frame->key_j);

    dest->key_k = get_key_state_based_on_last_state(last_frame->key_k, current_frame->key_k);

    dest->key_l = get_key_state_based_on_last_state(last_frame->key_l, current_frame->key_l);

    dest->key_m = get_key_state_based_on_last_state(last_frame->key_m, current_frame->key_m);

    dest->key_n = get_key_state_based_on_last_state(last_frame->key_n, current_frame->key_n);

    dest->key_o = get_key_state_based_on_last_state(last_frame->key_o, current_frame->key_o);

    dest->key_p = get_key_state_based_on_last_state(last_frame->key_p, current_frame->key_p);

    dest->key_q = get_key_state_based_on_last_state(last_frame->key_q, current_frame->key_q);

    dest->key_r = get_key_state_based_on_last_state(last_frame->key_r, current_frame->key_r);

    dest->key_s = get_key_state_based_on_last_state(last_frame->key_s, current_frame->key_s);

    dest->key_t = get_key_state_based_on_last_state(last_frame->key_t, current_frame->key_t);

    dest->key_u = get_key_state_based_on_last_state(last_frame->key_u, current_frame->key_u);

    dest->key_v = get_key_state_based_on_last_state(last_frame->key_v, current_frame->key_v);

    dest->key_w = get_key_state_based_on_last_state(last_frame->key_w, current_frame->key_w);

    dest->key_x = get_key_state_based_on_last_state(last_frame->key_x, current_frame->key_x);

    dest->key_y = get_key_state_based_on_last_state(last_frame->key_y, current_frame->key_y);

    dest->key_z = get_key_state_based_on_last_state(last_frame->key_z, current_frame->key_z);

    dest->key_left_bracket = get_key_state_based_on_last_state(last_frame->key_left_bracket,
                                                               current_frame->key_left_bracket);

    dest->key_backslash = get_key_state_based_on_last_state(last_frame->key_backslash, current_frame->key_backslash);

    dest->key_right_bracket = get_key_state_based_on_last_state(last_frame->key_right_bracket,
                                                                current_frame->key_right_bracket);

    dest->key_grave_accent = get_key_state_based_on_last_state(last_frame->key_grave_accent,
                                                               current_frame->key_grave_accent);

    dest->key_world_1 = get_key_state_based_on_last_state(last_frame->key_world_1, current_frame->key_world_1);

    dest->key_world_2 = get_key_state_based_on_last_state(last_frame->key_world_2, current_frame->key_world_2);


    dest->key_escape = get_key_state_based_on_last_state(last_frame->key_escape, current_frame->key_escape);

    dest->key_enter = get_key_state_based_on_last_state(last_frame->key_enter, current_frame->key_enter);

    dest->key_tab = get_key_state_based_on_last_state(last_frame->key_tab, current_frame->key_tab);

    dest->key_backspace = get_key_state_based_on_last_state(last_frame->key_backspace, current_frame->key_backspace);

    dest->key_insert = get_key_state_based_on_last_state(last_frame->key_insert, current_frame->key_insert);

    dest->key_delete = get_key_state_based_on_last_state(last_frame->key_delete, current_frame->key_delete);

    dest->key_right = get_key_state_based_on_last_state(last_frame->key_right, current_frame->key_right);

    dest->key_left = get_key_state_based_on_last_state(last_frame->key_left, current_frame->key_left);

    dest->key_down = get_key_state_based_on_last_state(last_frame->key_down, current_frame->key_down);

    dest->key_up = get_key_state_based_on_last_state(last_frame->key_up, current_frame->key_up);

    dest->key_page_up = get_key_state_based_on_last_state(last_frame->key_page_up, current_frame->key_page_up);

    dest->key_page_down = get_key_state_based_on_last_state(last_frame->key_page_down, current_frame->key_page_down);

    dest->key_home = get_key_state_based_on_last_state(last_frame->key_home, current_frame->key_home);

    dest->key_end = get_key_state_based_on_last_state(last_frame->key_end, current_frame->key_end);

    dest->key_caps_lock = get_key_state_based_on_last_state(last_frame->key_caps_lock, current_frame->key_caps_lock);

    get_key_state_based_on_last_state(last_frame->key_scroll_lock,
                                      dest->key_scroll_lock = current_frame->key_scroll_lock);

    dest->key_num_lock = get_key_state_based_on_last_state(last_frame->key_num_lock, current_frame->key_num_lock);

    dest->key_print_screen = get_key_state_based_on_last_state(last_frame->key_print_screen,
                                                               current_frame->key_print_screen);

    dest->key_pause = get_key_state_based_on_last_state(last_frame->key_pause, current_frame->key_pause);

    dest->key_f1 = get_key_state_based_on_last_state(last_frame->key_f1, current_frame->key_f1);

    dest->key_f2 = get_key_state_based_on_last_state(last_frame->key_f2, current_frame->key_f2);

    dest->key_f3 = get_key_state_based_on_last_state(last_frame->key_f3, current_frame->key_f3);

    dest->key_f4 = get_key_state_based_on_last_state(last_frame->key_f4, current_frame->key_f4);

    dest->key_f5 = get_key_state_based_on_last_state(last_frame->key_f5, current_frame->key_f5);

    dest->key_f6 = get_key_state_based_on_last_state(last_frame->key_f6, current_frame->key_f6);

    dest->key_f7 = get_key_state_based_on_last_state(last_frame->key_f7, current_frame->key_f7);

    dest->key_f8 = get_key_state_based_on_last_state(last_frame->key_f8, current_frame->key_f8);

    dest->key_f9 = get_key_state_based_on_last_state(last_frame->key_f9, current_frame->key_f9);

    dest->key_f10 = get_key_state_based_on_last_state(last_frame->key_f10, current_frame->key_f10);

    dest->key_f11 = get_key_state_based_on_last_state(last_frame->key_f11, current_frame->key_f11);

    dest->key_f12 = get_key_state_based_on_last_state(last_frame->key_f12, current_frame->key_f12);

    dest->key_f13 = get_key_state_based_on_last_state(last_frame->key_f13, current_frame->key_f13);

    dest->key_f14 = get_key_state_based_on_last_state(last_frame->key_f14, current_frame->key_f14);

    dest->key_f15 = get_key_state_based_on_last_state(last_frame->key_f15, current_frame->key_f15);

    dest->key_f16 = get_key_state_based_on_last_state(last_frame->key_f16, current_frame->key_f16);

    dest->key_f17 = get_key_state_based_on_last_state(last_frame->key_f17, current_frame->key_f17);

    dest->key_f18 = get_key_state_based_on_last_state(last_frame->key_f18, current_frame->key_f18);

    dest->key_f19 = get_key_state_based_on_last_state(last_frame->key_f19, current_frame->key_f19);

    dest->key_f20 = get_key_state_based_on_last_state(last_frame->key_f20, current_frame->key_f20);

    dest->key_f21 = get_key_state_based_on_last_state(last_frame->key_f21, current_frame->key_f21);

    dest->key_f22 = get_key_state_based_on_last_state(last_frame->key_f22, current_frame->key_f22);

    dest->key_f23 = get_key_state_based_on_last_state(last_frame->key_f23, current_frame->key_f23);

    dest->key_f24 = get_key_state_based_on_last_state(last_frame->key_f24, current_frame->key_f24);

    dest->key_f25 = get_key_state_based_on_last_state(last_frame->key_f25, current_frame->key_f25);

    dest->key_kp_0 = get_key_state_based_on_last_state(last_frame->key_kp_0, current_frame->key_kp_0);

    dest->key_kp_1 = get_key_state_based_on_last_state(last_frame->key_kp_1, current_frame->key_kp_1);

    dest->key_kp_2 = get_key_state_based_on_last_state(last_frame->key_kp_2, current_frame->key_kp_2);

    dest->key_kp_3 = get_key_state_based_on_last_state(last_frame->key_kp_3, current_frame->key_kp_3);

    dest->key_kp_4 = get_key_state_based_on_last_state(last_frame->key_kp_4, current_frame->key_kp_4);

    dest->key_kp_5 = get_key_state_based_on_last_state(last_frame->key_kp_5, current_frame->key_kp_5);

    dest->key_kp_6 = get_key_state_based_on_last_state(last_frame->key_kp_6, current_frame->key_kp_6);

    dest->key_kp_7 = get_key_state_based_on_last_state(last_frame->key_kp_7, current_frame->key_kp_7);

    dest->key_kp_8 = get_key_state_based_on_last_state(last_frame->key_kp_8, current_frame->key_kp_8);

    dest->key_kp_9 = get_key_state_based_on_last_state(last_frame->key_kp_9, current_frame->key_kp_9);

    dest->key_kp_decimal = get_key_state_based_on_last_state(last_frame->key_kp_decimal,
                                                             current_frame->key_kp_decimal);

    dest->key_kp_divide = get_key_state_based_on_last_state(last_frame->key_kp_divide, current_frame->key_kp_divide);

    get_key_state_based_on_last_state(last_frame->key_kp_multiply,
                                      dest->key_kp_multiply = current_frame->key_kp_multiply);

    get_key_state_based_on_last_state(last_frame->key_kp_subtract,
                                      dest->key_kp_subtract = current_frame->key_kp_subtract);

    dest->key_kp_add = get_key_state_based_on_last_state(last_frame->key_kp_add, current_frame->key_kp_add);

    dest->key_kp_enter = get_key_state_based_on_last_state(last_frame->key_kp_enter, current_frame->key_kp_enter);

    dest->key_kp_equal = get_key_state_based_on_last_state(last_frame->key_kp_equal, current_frame->key_kp_equal);

    dest->key_left_shift = get_key_state_based_on_last_state(last_frame->key_left_shift,
                                                             current_frame->key_left_shift);

    dest->key_left_control = get_key_state_based_on_last_state(last_frame->key_left_control,
                                                               current_frame->key_left_control);

    dest->key_left_alt = get_key_state_based_on_last_state(last_frame->key_left_alt, current_frame->key_left_alt);

    dest->key_left_super = get_key_state_based_on_last_state(last_frame->key_left_super,
                                                             current_frame->key_left_super);

    get_key_state_based_on_last_state(last_frame->key_right_shift,
                                      dest->key_right_shift = current_frame->key_right_shift);

    dest->key_right_control = get_key_state_based_on_last_state(last_frame->key_right_control,
                                                                current_frame->key_right_control);

    dest->key_right_alt = get_key_state_based_on_last_state(last_frame->key_right_alt, current_frame->key_right_alt);

    get_key_state_based_on_last_state(last_frame->key_right_super,
                                      dest->key_right_super = current_frame->key_right_super);

    dest->key_menu = get_key_state_based_on_last_state(last_frame->key_menu, current_frame->key_menu);

}

void update_input() {
    glfwPollEvents();
    
    update_input_state(&current_frame);
    update_input_based_on_last_frame(&last_frame, &current_frame, &current_frame);
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

bool get_key_pressed(key_code_t key) {
    key_state_t state = get_key_state(key);
    return state == KEY_STATE_PRESSED;
}

bool get_key_up(key_code_t key) {
    key_state_t state = get_key_state(key);
    return state == KEY_STATE_UP;
}

bool get_key_down(key_code_t key) {
    key_state_t state = get_key_state(key);
    return state == KEY_STATE_DOWN;
}