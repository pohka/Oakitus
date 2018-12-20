#ifndef STYLE_H
#define STYLE_H

#include <core/types.h>
#include <string>
#include <vector>
#include "color.h"
#include <unordered_map>
#include "ui_def.h"


namespace oak
{
  namespace style
  {
    cnum width = 0;
    cnum height = 1;
    cnum padding_left = 2;
    cnum padding_right = 3;
    cnum padding_top = 4;
    cnum padding_bottom = 5;
    cnum margin_left = 6;
    cnum margin_right = 7;
    cnum margin_top = 8;
    cnum margin_bottom = 9;
    cnum font_size = 10;
    cnum last_attr = 11;
  }

  namespace ui
  {
    

    //struct StyleBox
    //{
    //  float left = 0.0f;
    //  float right = 0.0f;
    //  float top = 0.0f;
    //  float bottom = 0.0f;
    //};

    struct Style
    {
      Style(std::string className);

      std::vector<std::string> classList;
   //   float w = -1.0f; //auto
   //   float h = -1.0f; //auto
   //   StyleBox padding;
    //  StyleBox margin;
      uchar position = UI_POSITION_RELATIVE;
      Color color = COLOR_NULL;
    //  float fontSize = 20.0f;
      
      std::vector<float> attrs = std::vector<float>(oak::style::last_attr);
      
      static constexpr float NULL_ATTR = std::numeric_limits<float>::infinity();

      void setPadding(float x, float y);
      void setMargin(float x, float y);
    };
  }
}

#endif