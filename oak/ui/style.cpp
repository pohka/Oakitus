#include "style.h"
#include <limits>
#include <core/string_help.h>
#include <debug.h>
#include <cctype>

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

  }

  if (key == "height")
  {
    attrs.insert_or_assign(STYLE_HEIGHT, num);
  }
}

bool Style::parseNumber(std::string val, float& num)
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
