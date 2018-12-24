#include "style_parser.h"
#include <core/string_help.h>
#include <debug.h>
#include <cctype>
#include <core/fmath.h>
#include <math.h>
#include "ui_def.h"

using namespace ion;

bool StyleParser::parseNumber(const std::string& val, float& num)
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

void StyleParser::parseColor(
  std::string& val, 
  std::vector<float>& rgba
)
{
  if (val.size() < 4)
  {
    LOG << "---STYLE ERROR---| invalid color value: '" << val << "'";
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
    if (val.size() < 10)
    {
      LOG << "---STYLE ERROR---| invalid color value: '" << val << "'";
    }
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
    if (els.size() < 3)
    {
      LOG << "---STYLE ERROR---| invalid color value: '" << val << "'";
      return;
    }
    //rgb
    float v;
    for (uint i = 0; i < els.size() && i < 3; i++)
    {
      if (oak::StringHelp::isNumber(els[i]))
      {
        v = std::stof(els[i]) / 255.0f;
        oak::FMath::clamp(v, 0.0f, 1.0f);
      }
      else
      {
        v = 0.0f;
      }
      rgba.push_back(v);
    }
    //alpha
    if (els.size() > 3 && oak::StringHelp::isNumber(els[3]))
    {
      float alpha = std::stof(els[3]);
      oak::FMath::clamp(alpha, 0.0f, 1.0f);
      rgba.push_back(alpha);
    }
  }
}

float StyleParser::hexToDecimal(std::string& str)
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

float StyleParser::hexToDecimal(char ch)
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

unsigned char StyleParser::parseStateID(std::string state)
{
  if (state == "root")
  {
    return STYLE_STATE_ROOT;
  }
  else if (state == "hover")
  {
    return STYLE_STATE_HOVER;
  }
  else if (state == "focus")
  {
    return STYLE_STATE_FOCUS;
  }
  return STYLE_STATE_NONE;
}