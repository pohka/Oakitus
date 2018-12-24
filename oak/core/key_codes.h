#ifndef KEYCODES_H
#define KEYCODES_H

#include <core/types.h>
#include <core/kv_array.h>

namespace oak
{
  snum KEYCODE_SPACE = 32;
  snum KEYCODE_APOSTROPHE = 39; ; // '
  snum KEYCODE_COMMA = 44; ; // ;
  snum KEYCODE_MINUS = 45; // -
  snum KEYCODE_PERIOD = 46; // .
  snum KEYCODE_SLASH = 47; // /
  snum KEYCODE_NUM_0 = 48;
  snum KEYCODE_NUM_1 = 49;
  snum KEYCODE_NUM_2 = 50;
  snum KEYCODE_NUM_3 = 51;
  snum KEYCODE_NUM_4 = 52;
  snum KEYCODE_NUM_5 = 53;
  snum KEYCODE_NUM_6 = 54;
  snum KEYCODE_NUM_7 = 55;
  snum KEYCODE_NUM_8 = 56;
  snum KEYCODE_NUM_9 = 57;
  snum KEYCODE_SEMICOLON = 59; /* ; */
  snum KEYCODE_EQUALS = 61; /* = */
  snum KEYCODE_A = 65;
  snum KEYCODE_B = 66;
  snum KEYCODE_C = 67;
  snum KEYCODE_D = 68;
  snum KEYCODE_E = 69;
  snum KEYCODE_F = 70;
  snum KEYCODE_G = 71;
  snum KEYCODE_H = 72;
  snum KEYCODE_I = 73;
  snum KEYCODE_J = 74;
  snum KEYCODE_K = 75;
  snum KEYCODE_L = 76;
  snum KEYCODE_M = 77;
  snum KEYCODE_N = 78;
  snum KEYCODE_O = 79;
  snum KEYCODE_P = 80;
  snum KEYCODE_Q = 81;
  snum KEYCODE_R = 82;
  snum KEYCODE_S = 83;
  snum KEYCODE_T = 84;
  snum KEYCODE_U = 85;
  snum KEYCODE_V = 86;
  snum KEYCODE_W = 87;
  snum KEYCODE_X = 88;
  snum KEYCODE_Y = 89;
  snum KEYCODE_Z = 90;
  snum KEYCODE_LEFT_BRACKET = 91; /* [ */
  snum KEYCODE_BACKSLASH = 92; /* \ */
  snum KEYCODE_RIGHT_BRACKET = 93; /* ] */
  snum KEYCODE_GRAVE_ACCENT = 96; /* ` */
  snum KEYCODE_ESCAPE = 256;
  snum KEYCODE_ENTER = 257;
  snum KEYCODE_TAB = 258;
  snum KEYCODE_BACKSPACE = 259;
  snum KEYCODE_INSERT = 260;
  snum KEYCODE_DELETE_KEY = 261;
  snum KEYCODE_RIGHT = 262;
  snum KEYCODE_LEFT = 263;
  snum KEYCODE_DOWN = 264;
  snum KEYCODE_UP = 265;
  snum KEYCODE_PAGE_UP = 266;
  snum KEYCODE_PAGE_DOWN = 267;
  snum KEYCODE_HOME = 268;
  snum KEYCODE_END = 269;
  snum KEYCODE_CAPS_LOCK = 280;
  snum KEYCODE_SCROLL_LOCK = 281;
  snum KEYCODE_NUM_LOCK = 282;
  snum KEYCODE_PRINT_SCREEN = 283;
  snum KEYCODE_PAUSE = 284;
  snum KEYCODE_F1 = 290;
  snum KEYCODE_F2 = 291;
  snum KEYCODE_F3 = 292;
  snum KEYCODE_F4 = 293;
  snum KEYCODE_F5 = 294;
  snum KEYCODE_F6 = 295;
  snum KEYCODE_F7 = 296;
  snum KEYCODE_F8 = 297;
  snum KEYCODE_F9 = 298;
  snum KEYCODE_F10 = 299;
  snum KEYCODE_F11 = 300;
  snum KEYCODE_F12 = 301;
  snum KEYCODE_KP_0 = 320;
  snum KEYCODE_KP_1 = 321;
  snum KEYCODE_KP_2 = 322;
  snum KEYCODE_KP_3 = 323;
  snum KEYCODE_KP_4 = 324;
  snum KEYCODE_KP_5 = 325;
  snum KEYCODE_KP_6 = 326;
  snum KEYCODE_KP_7 = 327;
  snum KEYCODE_KP_8 = 328;
  snum KEYCODE_KP_9 = 329;
  snum KEYCODE_KP_DECIMAL = 330;
  snum KEYCODE_KP_DIVIDE = 331;
  snum KEYCODE_KP_MULTIPLY = 332;
  snum KEYCODE_KP_SUBTRACT = 333;
  snum KEYCODE_KP_ADD = 334;
  snum KEYCODE_KP_ENTER = 335;
  snum KEYCODE_KP_EQUAL = 336;
  snum KEYCODE_LEFT_SHIFT = 340;
  snum KEYCODE_LEFT_CONTROL = 341;
  snum KEYCODE_LEFT_ALT = 342;
  snum KEYCODE_LEFT_SUPER = 343;
  snum KEYCODE_RIGHT_SHIFT = 344;
  snum KEYCODE_RIGHT_CONTROL = 345;
  snum KEYCODE_RIGHT_ALT = 346;
  snum KEYCODE_RIGHT_SUPER = 347;

  //copy of all the keys as an ineger; so they can be iteratored
  const ushort glKeys[] = {
    32, //space
    39,
    44,
    45,
    46,
    47,
    48,
    49,
    50,
    51,
    52,
    53,
    54,
    55,
    56,
    57,
    59,
    61,
    65, //A
    66,
    67,
    68,
    69,
    70,
    71,
    72,
    73,
    74,
    75,
    76,
    77,
    78,
    79,
    80,
    81,
    82,
    83,
    84,
    85,
    86,
    87,
    88,
    89,
    90, //Z
    91, /* [ */
    92, /* \ */
    93, /* ] */
    96, /* ` */
    256, //escape
    257,
    258,
    259,
    260,
    261,
    262,
    263,
    264,
    265,
    266,
    267,
    268,
    269,
    280,
    281,
    282,
    283,
    284,
    290, //F1
    291,
    292,
    293,
    294,
    295,
    296,
    297,
    298,
    299,
    300,
    301,
    320,
    321,
    322,
    323,
    324,
    325,
    326,
    327,
    328,
    329,
    330,
    331,
    332,
    333,
    334,
    335,
    336,
    340,
    341,
    342,
    343,
    344,
    345,
    346,
    347
  };

  cnum MOUSE_BUTTON_LEFT = 0;
  cnum MOUSE_BUTTON_RIGHT = 1;
  cnum MOUSE_BUTTON_MIDDLE = 2;
  cnum MOUSE_BUTTON_LAST = 3;
};

#endif
