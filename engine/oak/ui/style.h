#pragma once
#ifndef STYLE_H
#define STYLE_H

#include <oak/core/types.h>
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
    Style(const std::string& selector);

    //constructor that is used with StyleLoader
    Style(
      std::string selector, 
      std::unordered_map<std::string, std::string>& attrs
    );

    ~Style();

    //style attributes
    std::string selector = "";
    std::unordered_map<uchar, float> attrs;
    uchar position = UI_POSITION_RELATIVE;
    Color color = COLOR_NULL;
    
    //try add the pseudo style, if the id already exists it returns false
    bool addStateStyle(uchar id, Style* style);
      
    //set padding shorthand
    void setPadding(float x, float y);

    //set margins shorthand
    void setMargin(float x, float y);

    //get an attribute
    float get(uchar key);

    //set an attribute
    void set(uchar key, float val);

    //set an attribute by string values
    void set(std::string key, std::string val);

    Style* findStateStyle(uchar state);
    

  private :
    //converts css string key to cnum key
    void setNum(const std::string& key, const std::string& val, cnum STYLE_KEY);
    std::unordered_map<uchar, Style*> stateStyles;

  };
}

#endif