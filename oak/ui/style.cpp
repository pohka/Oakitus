#include "style.h"
#include <limits>
#include <core/string_help.h>
#include <debug.h>
#include <cctype>
#include <core/fmath.h>
#include <math.h>

using namespace ion;

Style::Style(std::string className)
{
  oak::StringHelp::split(className, classList, ' ');
  attrs.insert_or_assign(STYLE_WIDTH, STYLE_VAL_AUTO);
  attrs.insert_or_assign(STYLE_HEIGHT, STYLE_VAL_AUTO);
}

Style::Style(
  std::vector<std::string>& classList,
  std::unordered_map<std::string, std::string>& attrs
)
{
  for (std::string cls : classList)
  {
    this->classList.push_back(cls);
  }
  for (auto it = attrs.begin(); it != attrs.end(); it++)
  {
    set(it->first, it->second);
  }
}

void Style::setPadding(float x, float y)
{
  attrs.insert_or_assign(STYLE_PADDING_LEFT, x);
  attrs.insert_or_assign(STYLE_PADDING_RIGHT, x);
  attrs.insert_or_assign(STYLE_PADDING_TOP, y);
  attrs.insert_or_assign(STYLE_PADDING_BOTTOM, y);
}

void Style::setMargin(float x, float y)
{
  attrs.insert_or_assign(STYLE_MARGIN_LEFT, x);
  attrs.insert_or_assign(STYLE_MARGIN_RIGHT, x);
  attrs.insert_or_assign(STYLE_MARGIN_TOP, y);
  attrs.insert_or_assign(STYLE_MARGIN_BOTTOM, y);
}

float Style::get(uchar key)
{
  auto it = attrs.find(key);
  if (it != attrs.end())
  {
    return it->second;
  }

  return STYLE_VAL_AUTO;
}

void Style::set(uchar key, float val)
{
  attrs.insert_or_assign(key, val);
}

void Style::set(std::string key, std::string val)
{
  std::vector<std::string> els;

  if (key == "position")
  {
    if (val == "absolute")
    {
      this->position = UI_POSITION_ABSOLUTE;
    }
    else
    {
      this->position = UI_POSITION_RELATIVE;
    }
  }
  else if (key == "color")
  {
    std::vector<float> rgba;
    parseColor(val, rgba);
    if (rgba.size() >= 3)
    {
      this->color.r = rgba[0];
      this->color.g = rgba[1];
      this->color.b = rgba[2];
      if (rgba.size() >= 4)
      {
        color.a = rgba[3];
      }
      else
      {
        color.a = 1.0f;
      }
    }
  }
  //padding shorthand
  else if (key == "padding")
  {
    oak::StringHelp::split(val, els, ' ');
  //padding:30px 30px 10px 15px;
    if (els.size() >= 4)
    {
      setNum(key, els[0], STYLE_PADDING_TOP);
      setNum(key, els[1], STYLE_PADDING_RIGHT);
      setNum(key, els[2], STYLE_PADDING_BOTTOM);
      setNum(key, els[3], STYLE_PADDING_LEFT);
    }
  //padding:20px 30px;
    else if (els.size() >= 2)
    {
      setNum(key, els[0], STYLE_PADDING_TOP);
      setNum(key, els[0], STYLE_PADDING_BOTTOM);
      setNum(key, els[1], STYLE_PADDING_LEFT);
      setNum(key, els[1], STYLE_PADDING_RIGHT);
    }
    //padding:30px;
    else if(els.size() == 1)
    {
      setNum(key, els[0], STYLE_PADDING_LEFT);
      setNum(key, els[0], STYLE_PADDING_RIGHT);
      setNum(key, els[0], STYLE_PADDING_TOP);
      setNum(key, els[0], STYLE_PADDING_BOTTOM);
    }
  }
  //margin shorthand
  else if (key == "margin")
  {
    oak::StringHelp::split(val, els, ' ');
    //margin:30px 30px 10px 15px;
    if (els.size() >= 4)
    {
      setNum(key, els[0], STYLE_MARGIN_TOP);
      setNum(key, els[1], STYLE_MARGIN_RIGHT);
      setNum(key, els[2], STYLE_MARGIN_BOTTOM);
      setNum(key, els[3], STYLE_MARGIN_LEFT);
    }
    //margin:20px 30px;
    else if (els.size() >= 2)
    {
      setNum(key, els[0], STYLE_MARGIN_TOP);
      setNum(key, els[0], STYLE_MARGIN_BOTTOM);
      setNum(key, els[1], STYLE_MARGIN_LEFT);
      setNum(key, els[1], STYLE_MARGIN_RIGHT);
    }
    //margin:30px;
    else if (els.size() == 1)
    {
      setNum(key, els[0], STYLE_MARGIN_LEFT);
      setNum(key, els[0], STYLE_MARGIN_RIGHT);
      setNum(key, els[0], STYLE_MARGIN_TOP);
      setNum(key, els[0], STYLE_MARGIN_BOTTOM);
    }
  }
  //basic number key values
  //--------------
  else if (key == "width")
  {
    setNum(key, val, STYLE_WIDTH);
  }
  else if (key == "height")
  {
    setNum(key, val, STYLE_HEIGHT);
  }
  else if (key == "padding-left")
  {
    setNum(key, val, STYLE_PADDING_LEFT);
  }
  else if (key == "padding-right")
  {
    setNum(key, val, STYLE_PADDING_RIGHT);
  }
  else if (key == "padding-top")
  {
    setNum(key, val, STYLE_PADDING_TOP);
  }
  else if (key == "padding-bottom")
  {
    setNum(key, val, STYLE_PADDING_BOTTOM);
  }
  else if (key == "margin-left")
  {
    setNum(key, val, STYLE_MARGIN_LEFT);
  }
  else if (key == "margin-right")
  {
    setNum(key, val, STYLE_MARGIN_RIGHT);
  }
  else if (key == "margin-top")
  {
    setNum(key, val, STYLE_MARGIN_TOP);
  }
  else if (key == "margin-bottom")
  {
    setNum(key, val, STYLE_MARGIN_BOTTOM);
  }
  else if (key == "font-size")
  {
    setNum(key, val, STYLE_FONT_SIZE);
  }
}

void Style::setNum(const std::string& key, const std::string& val, cnum STYLE_KEY)
{
  float num;
  bool isValidNumber = parseNumber(val, num);
  if (!isValidNumber)
  {
    LOG << "---STYLE ERROR---| '." << classList[0] <<
      "' invalid attribute: " << key << ":" << val << ";";
    return;
  }
  else
  {
    attrs.insert_or_assign(STYLE_KEY, num);
  }
}

bool Style::parseNumber(const std::string& val, float& num)
{
  if (val == "auto")
  {
    num = STYLE_VAL_AUTO;
    return true;
  }


  char c; 
  bool decimalPt = false;
  for (uint i = 0; i < val.size(); i++)
  {
    c = val[i];
    //not a number character
    if (c < '0' || c > '9')
    {
      //exception for first decimal point
      if (c == '.' && !decimalPt && i > 0)
      {
        decimalPt = true;
      }
      else
      {
        std::string numStr = val.substr(0, i);
        if (numStr.size() > 0)
        {
          num = std::stof(numStr);
          return true;
        }
        else
        {
          return false;
        }
      }
    }
  }
  //all characters are digits
  num = std::stof(val);
  return true;
}

void Style::parseColor(
  std::string& val, 
  std::vector<float>& rgba
)
{
  if (val.size() < 4)
  {
    return;
  }

  //find the way the color is specified 
  const char HEX_COLOR_RGB = 3;
  const char HEX_COLOR_RGBA = 4;
  const char HEX_COLOR_RRGGBB = 6;
  const char HEX_COLOR_RRGGBBAA = 8;
  uint type;

  oak::StringHelp::removeChar(val, ' '); //remove all spaces
  rgba.clear();
  std::string str;

  if (val[0] == '#')
  {
    str = val.substr(1);
    type = str.size();

    //HEX rgb and rgba
    if (type == HEX_COLOR_RGB || type == HEX_COLOR_RGBA)
    {
      for (uint i = 0; i < str.size() && i < HEX_COLOR_RGB; i++)
      {
        float r = hexToDecimal(str[i]) / 15.0f;
        rgba.push_back(r);
      }

      //alpha
      if (type == HEX_COLOR_RGBA)
      {
        std::string alphaHex = str.substr(HEX_COLOR_RGB);
        float r = hexToDecimal(str[3]) / 15.0f;
        rgba.push_back(r);
      }
      else
      {
        rgba.push_back(1.0f);
      }
    }
    //HEX rrggbb and rrggbbaa
    else if (type == HEX_COLOR_RRGGBB || type == HEX_COLOR_RRGGBBAA)
    {
      std::string col;
      for (uint i = 0; i < str.size() && i < HEX_COLOR_RRGGBB; i+=2)
      {
        col = str.substr(i, 2);
        float r = hexToDecimal(col) / 255.0f;
        rgba.push_back(r);
      }

      if (type == HEX_COLOR_RRGGBBAA)
      {
        std::string alphaHex = str.substr(HEX_COLOR_RRGGBB);
        float r = hexToDecimal(alphaHex) / 255.0f;
        rgba.push_back(r);
      }
      else
      {
        rgba.push_back(1.0f);
      }
    }
    //hex invalud number of characters
    else
    {
      LOG << "---STYLE ERROR---| invalid color value: '" << val << "'";
    }
  }
  //rgb(...) and rgba(...)
  else if(val.substr(0,3) == "rgb")
  {
    //rgb(...)
    if (val[3] != 'a')
    {
      str = val.substr(4);
    }
    //rgba(...)
    else
    {
      str = val.substr(5);
    }
    str.pop_back(); 
    //str e.g. "255,255,255" i.e. no spaces and no brackets
    std::vector<std::string> els;
    oak::StringHelp::split(str, els, ',');
    //rgb
    for (uint i = 0; i < els.size() && i < 3; i++)
    {
      float v = std::stof(els[i]) / 255.0f;
      oak::FMath::clamp(v, 0.0f, 1.0f);
      rgba.push_back(v);
    }
    //alpha
    if (els.size() > 3)
    {
      float alpha = std::stof(els[3]);
      oak::FMath::clamp(alpha, 0.0f, 1.0f);
      rgba.push_back(alpha);
    }
  }
}


float Style::hexToDecimal(std::string& str)
{
  int count = 0;
  float val = 0.0f;
  char ch;
  const std::string hex = "0123456789ABCDEF";

  for (int i = str.size() - 1; i >= 0; i--)
  {
    ch = toupper(str[i]);
    for (uint d = 0; d < hex.size(); d++)
    {
      if (ch == hex[d])
      {
        if (count == 0)
        {
          val += d;
        }
        else
        {
          val += (float)(d * pow(hex.size(), count));
        }
      }
    }
    count++;
  }

  return val;
}

float Style::hexToDecimal(char ch)
{
  const std::string hex = "0123456789ABCDEF";
  ch = toupper(ch);
  for (uint d = 0; d < hex.size(); d++)
  {
    if (ch == hex[d])
    {
      return (float)(d);
    }
  }

  return 0.0f;
}