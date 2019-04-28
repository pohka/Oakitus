#pragma once
#ifndef UI_DEF_H
#define UI_DEF_H

#include <oak/core/types.h>
#include "color.h"
#include <limits>

cnum UI_NODE_LABEL = 0;
cnum UI_NODE_IMAGE = 1;
cnum UI_NODE_DIV = 2;
cnum UI_NODE_TEMPLATE = 3;


//alignment values
const float UI_ALIGN_HORZ_LEFT = -1.0f;
const float UI_ALIGN_HORZ_CENTER = 0.0f;
const float UI_ALIGN_HORZ_RIGHT = 1.0f;

const float UI_ALIGN_VERT_TOP = 1.0f;
const float UI_ALIGN_VERT_MIDDLE = 0.0f;
const float UI_ALIGN_VERT_BOTTOM = -1.0f;

const uint FONT_LOADED_SIZE = 64;

cnum UI_POSITION_RELATIVE = 0;
cnum UI_POSITION_ABSOLUTE = 1;

const static ion::Color COLOR_RED = { 1.0f, 0.0f, 0.0f, 1.0f };
const static ion::Color COLOR_GREEN = { 0.0f, 1.0f, 0.0f, 1.0f };
const static ion::Color COLOR_BLUE = { 0.0f, 0.0f, 1.0f, 1.0f };
const static ion::Color COLOR_BLACK = { 0.0f, 0.0f, 0.0f, 1.0f };
const static ion::Color COLOR_WHITE = { 1.0f, 1.0f, 1.0f, 1.0f };
const static ion::Color COLOR_NULL = { -1.0f, -1.0f, -1.0f, -1.0f };
const static ion::Color COLOR_DEFAULT_FONT = { 1.0f, 1.0f, 1.0f, 1.0f };

cnum STYLE_WIDTH = 0;
cnum STYLE_HEIGHT = 1;
cnum STYLE_PADDING_LEFT = 2;
cnum STYLE_PADDING_RIGHT = 3;
cnum STYLE_PADDING_TOP = 4;
cnum STYLE_PADDING_BOTTOM = 5;
cnum STYLE_MARGIN_LEFT = 6;
cnum STYLE_MARGIN_RIGHT = 7;
cnum STYLE_MARGIN_TOP = 8;
cnum STYLE_MARGIN_BOTTOM = 9;
cnum STYLE_FONT_SIZE = 10;
cnum STYLE_LAST_ATTR = 11;

cnum STYLE_STATE_NONE = 0;
cnum STYLE_STATE_ROOT = 1;
cnum STYLE_STATE_HOVER = 2;
cnum STYLE_STATE_FOCUS = 3;

//const float STYLE_NULL_ATTR = std::numeric_limits<float>::infinity();
const float STYLE_DEFAULT_FONT_SIZE = 20.0f;
constexpr float STYLE_VAL_AUTO = std::numeric_limits<float>::infinity();

#endif