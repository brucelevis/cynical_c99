//
// Created by temdisponivel on 02/06/2018.
//

#ifndef RAW_GL_INPUT_H
#define RAW_GL_INPUT_H

#include "common.h"

typedef enum {

    KEY_SPACE = GLFW_KEY_SPACE,
    KEY_APOSTROPHE = GLFW_KEY_APOSTROPHE,
    KEY_COMMA = GLFW_KEY_COMMA,
    KEY_MINUS = GLFW_KEY_MINUS,
    KEY_PERIOD = GLFW_KEY_PERIOD,   
    KEY_SLASH = GLFW_KEY_SLASH,
    KEY_0 = GLFW_KEY_0,
    KEY_1 = GLFW_KEY_1,
    KEY_2 = GLFW_KEY_2,
    KEY_3 = GLFW_KEY_3,
    KEY_4 = GLFW_KEY_4,
    KEY_5 = GLFW_KEY_5,
    KEY_6 = GLFW_KEY_6,
    KEY_7 = GLFW_KEY_7,
    KEY_8 = GLFW_KEY_8,
    KEY_9 = GLFW_KEY_9,
    KEY_SEMICOLON = GLFW_KEY_SEMICOLON,
    KEY_EQUAL = GLFW_KEY_EQUAL,
    KEY_A = GLFW_KEY_A,
    KEY_B = GLFW_KEY_B,
    KEY_C = GLFW_KEY_C,
    KEY_D = GLFW_KEY_D,
    KEY_E = GLFW_KEY_E,
    KEY_F = GLFW_KEY_F,
    KEY_G = GLFW_KEY_G,
    KEY_H = GLFW_KEY_H,
    KEY_I = GLFW_KEY_I,
    KEY_J = GLFW_KEY_J,
    KEY_K = GLFW_KEY_K,
    KEY_L = GLFW_KEY_L,
    KEY_M = GLFW_KEY_M,
    KEY_N = GLFW_KEY_N,
    KEY_O = GLFW_KEY_O,
    KEY_P = GLFW_KEY_P,
    KEY_Q = GLFW_KEY_Q,
    KEY_R = GLFW_KEY_R,
    KEY_S = GLFW_KEY_S,
    KEY_T = GLFW_KEY_T,
    KEY_U = GLFW_KEY_U,
    KEY_V = GLFW_KEY_V,
    KEY_W = GLFW_KEY_W,
    KEY_X = GLFW_KEY_X,
    KEY_Y = GLFW_KEY_Y,
    KEY_Z = GLFW_KEY_Z,
    KEY_LEFT_BRACKET = GLFW_KEY_LEFT_BRACKET,
    KEY_BACKSLASH = GLFW_KEY_BACKSLASH,
    KEY_RIGHT_BRACKET = GLFW_KEY_RIGHT_BRACKET,
    KEY_GRAVE_ACCENT = GLFW_KEY_GRAVE_ACCENT,
    KEY_WORLD_1 = GLFW_KEY_WORLD_1,
    KEY_WORLD_2 = GLFW_KEY_WORLD_2,

    KEY_ESCAPE = GLFW_KEY_ESCAPE,
    KEY_ENTER = GLFW_KEY_ENTER,
    KEY_TAB = GLFW_KEY_TAB,
    KEY_BACKSPACE = GLFW_KEY_BACKSPACE,
    KEY_INSERT = GLFW_KEY_INSERT,
    KEY_DELETE = GLFW_KEY_DELETE,
    KEY_RIGHT = GLFW_KEY_RIGHT,
    KEY_LEFT = GLFW_KEY_LEFT,
    KEY_DOWN = GLFW_KEY_DOWN,
    KEY_UP = GLFW_KEY_UP,
    KEY_PAGE_UP = GLFW_KEY_PAGE_UP,
    KEY_PAGE_DOWN = GLFW_KEY_PAGE_DOWN,
    KEY_HOME = GLFW_KEY_HOME,
    KEY_END = GLFW_KEY_END,
    KEY_CAPS_LOCK = GLFW_KEY_CAPS_LOCK,
    KEY_SCROLL_LOCK = GLFW_KEY_SCROLL_LOCK,
    KEY_NUM_LOCK = GLFW_KEY_NUM_LOCK,
    KEY_PRINT_SCREEN = GLFW_KEY_PRINT_SCREEN,
    KEY_PAUSE = GLFW_KEY_PAUSE,
    KEY_F1 = GLFW_KEY_F1,
    KEY_F2 = GLFW_KEY_F2,
    KEY_F3 = GLFW_KEY_F3,
    KEY_F4 = GLFW_KEY_F4,
    KEY_F5 = GLFW_KEY_F5,
    KEY_F6 = GLFW_KEY_F6,
    KEY_F7 = GLFW_KEY_F7,
    KEY_F8 = GLFW_KEY_F8,
    KEY_F9 = GLFW_KEY_F9,
    KEY_F10 = GLFW_KEY_F10,
    KEY_F11 = GLFW_KEY_F11,
    KEY_F12 = GLFW_KEY_F12,
    KEY_F13 = GLFW_KEY_F13,
    KEY_F14 = GLFW_KEY_F14,
    KEY_F15 = GLFW_KEY_F15,
    KEY_F16 = GLFW_KEY_F16,
    KEY_F17 = GLFW_KEY_F17,
    KEY_F18 = GLFW_KEY_F18,
    KEY_F19 = GLFW_KEY_F19,
    KEY_F20 = GLFW_KEY_F20,
    KEY_F21 = GLFW_KEY_F21,
    KEY_F22 = GLFW_KEY_F22,
    KEY_F23 = GLFW_KEY_F23,
    KEY_F24 = GLFW_KEY_F24,
    KEY_F25 = GLFW_KEY_F25,
    KEY_KP_0 = GLFW_KEY_KP_0,
    KEY_KP_1 = GLFW_KEY_KP_1,
    KEY_KP_2 = GLFW_KEY_KP_2,
    KEY_KP_3 = GLFW_KEY_KP_3,
    KEY_KP_4 = GLFW_KEY_KP_4,
    KEY_KP_5 = GLFW_KEY_KP_5,
    KEY_KP_6 = GLFW_KEY_KP_6,
    KEY_KP_7 = GLFW_KEY_KP_7,
    KEY_KP_8 = GLFW_KEY_KP_8,
    KEY_KP_9 = GLFW_KEY_KP_9,
    KEY_KP_DECIMAL = GLFW_KEY_KP_DECIMAL,
    KEY_KP_DIVIDE = GLFW_KEY_KP_DIVIDE,
    KEY_KP_MULTIPLY = GLFW_KEY_KP_MULTIPLY,
    KEY_KP_SUBTRACT = GLFW_KEY_KP_SUBTRACT,
    KEY_KP_ADD = GLFW_KEY_KP_ADD,
    KEY_KP_ENTER = GLFW_KEY_KP_ENTER,
    KEY_KP_EQUAL = GLFW_KEY_KP_EQUAL,
    KEY_LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT,
    KEY_LEFT_CONTROL = GLFW_KEY_LEFT_CONTROL,
    KEY_LEFT_ALT = GLFW_KEY_LEFT_ALT,
    KEY_LEFT_SUPER = GLFW_KEY_LEFT_SUPER,
    KEY_RIGHT_SHIFT = GLFW_KEY_RIGHT_SHIFT,
    KEY_RIGHT_CONTROL = GLFW_KEY_RIGHT_CONTROL,
    KEY_RIGHT_ALT = GLFW_KEY_RIGHT_ALT,
    KEY_RIGHT_SUPER = GLFW_KEY_RIGHT_SUPER,
    KEY_MENU = GLFW_KEY_MENU,
} key_code_t;

typedef enum {
    KEY_STATE_NORMAL,
    KEY_STATE_PRESSED,
    KEY_STATE_UP,
    KEY_STATE_DOWN
} key_state_t;

typedef struct input_state {
    key_state_t key_space;
    key_state_t key_apostrophe;
    key_state_t key_comma;
    key_state_t key_minus;
    key_state_t key_period;
    key_state_t key_slash;
    key_state_t key_0;
    key_state_t key_1;
    key_state_t key_2;
    key_state_t key_3;
    key_state_t key_4;
    key_state_t key_5;
    key_state_t key_6;
    key_state_t key_7;
    key_state_t key_8;
    key_state_t key_9;
    key_state_t key_semicolon;
    key_state_t key_equal;
    key_state_t key_a;
    key_state_t key_b;
    key_state_t key_c;
    key_state_t key_d;
    key_state_t key_e;
    key_state_t key_f;
    key_state_t key_g;
    key_state_t key_h;
    key_state_t key_i;
    key_state_t key_j;
    key_state_t key_k;
    key_state_t key_l;
    key_state_t key_m;
    key_state_t key_n;
    key_state_t key_o;
    key_state_t key_p;
    key_state_t key_q;
    key_state_t key_r;
    key_state_t key_s;
    key_state_t key_t;
    key_state_t key_u;
    key_state_t key_v;
    key_state_t key_w;
    key_state_t key_x;
    key_state_t key_y;
    key_state_t key_z;
    key_state_t key_left_bracket;
    key_state_t key_backslash;
    key_state_t key_right_bracket;
    key_state_t key_grave_accent;
    key_state_t key_world_1;
    key_state_t key_world_2;    
    key_state_t key_escape;
    key_state_t key_enter;
    key_state_t key_tab;
    key_state_t key_backspace;
    key_state_t key_insert;
    key_state_t key_delete;
    key_state_t key_right;
    key_state_t key_left;
    key_state_t key_down;
    key_state_t key_up;
    key_state_t key_page_up;
    key_state_t key_page_down;
    key_state_t key_home;
    key_state_t key_end;
    key_state_t key_caps_lock;
    key_state_t key_scroll_lock;
    key_state_t key_num_lock;
    key_state_t key_print_screen;
    key_state_t key_pause;
    key_state_t key_f1;
    key_state_t key_f2;
    key_state_t key_f3;
    key_state_t key_f4;
    key_state_t key_f5;
    key_state_t key_f6;
    key_state_t key_f7;
    key_state_t key_f8;
    key_state_t key_f9;
    key_state_t key_f10;
    key_state_t key_f11;
    key_state_t key_f12;
    key_state_t key_f13;
    key_state_t key_f14;
    key_state_t key_f15;
    key_state_t key_f16;
    key_state_t key_f17;
    key_state_t key_f18;
    key_state_t key_f19;
    key_state_t key_f20;
    key_state_t key_f21;
    key_state_t key_f22;
    key_state_t key_f23;
    key_state_t key_f24;
    key_state_t key_f25;
    key_state_t key_kp_0;
    key_state_t key_kp_1;
    key_state_t key_kp_2;
    key_state_t key_kp_3;
    key_state_t key_kp_4;
    key_state_t key_kp_5;
    key_state_t key_kp_6;
    key_state_t key_kp_7;
    key_state_t key_kp_8;
    key_state_t key_kp_9;
    key_state_t key_kp_decimal;
    key_state_t key_kp_divide;
    key_state_t key_kp_multiply;
    key_state_t key_kp_subtract;
    key_state_t key_kp_add;
    key_state_t key_kp_enter;
    key_state_t key_kp_equal;
    key_state_t key_left_shift;
    key_state_t key_left_control;
    key_state_t key_left_alt;
    key_state_t key_left_super;
    key_state_t key_right_shift;
    key_state_t key_right_control;
    key_state_t key_right_alt;
    key_state_t key_right_super;
    key_state_t key_menu;
} input_state_t;

key_state_t get_key_state(key_code_t key);

void update_input();

bool get_key_pressed(key_code_t key);

bool get_key_up(key_code_t key);

bool get_key_down(key_code_t key);

#endif //RAW_GL_INPUT_H
