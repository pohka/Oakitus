#ifndef STYLE_H
#define STYLE_H

#include <core/types.h>
#include <string>
#include <vector>
#include "color.h"
#include <unordered_map>
#include "ui_def.h"
#include <unordered_map>


namespace ion
{
  struct Style
  {
    Style(std::string className);
    Style(
      std::vector<std::string>& classList, 
      std::unordered_map<std::string, std::string>& attrs
    );

    //attributes
    std::vector<std::string> classList;
    std::unordered_map<uchar, float> attrs;
    uchar position = UI_POSITION_RELATIVE;
    Color color = COLOR_NULL;
      
    //getter and setter functions
    void setPadding(float x, float y);
    void setMargin(float x, float y);
    float get(uchar key);
    void set(uchar key, float val);

    void set(std::string key, std::string val);
    static bool parseNumber(const std::string& val, float& num);
    static void parseColor(std::string& val, std::vector<float>& rgba);

  private :
    void setNum(const std::string& key, const std::string& val, cnum STYLE_KEY);

  };
}

#endif