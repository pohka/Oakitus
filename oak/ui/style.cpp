#include "style.h"
#include <limits>
#include <core/string_help.h>
#include <debug.h>

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
  if (key == "height")
  {
    float num = parseNumber(val);
    attrs.insert_or_assign(STYLE_HEIGHT, num);
    LOG << "added height," << classList[0] << ":" << num;
  }
}

float Style::parseNumber(std::string val)
{
  if (val == "auto")
  {
    return STYLE_VAL_AUTO;
  }

  char c; 
  bool decimalPt = false;
  for (uint i = 0; i < val.size(); i++)
  {
    c = val[i];
    if ((c < '0' || c > '9'))
    {
      if (c == '.' && !decimalPt)
      {
        decimalPt = true;
      }
      else
      {
        std::string numStr = val.substr(0, i);
        return std::stof(numStr);
      }
    }
  }
  return std::stof(val);
}