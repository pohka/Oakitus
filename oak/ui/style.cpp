#include "style.h"
#include <limits>

using namespace oak::ui;

Style::Style(std::string className)
{
  std::string delimiter = " ";
  int pos = 0;
  std::string token;
  while ((pos = className.find(delimiter)) != std::string::npos) 
  {
    token = className.substr(0, pos);
    classList.push_back(token);
    className.erase(0, pos + delimiter.length());
  }

  /*for (uint i=0; i<attrs.size(); i++)
  {
    attrs[i] = NULL_ATTR;
  }*/

  attrs.insert_or_assign(STYLE_WIDTH, STYLE_VAL_AUTO);
  attrs.insert_or_assign(STYLE_HEIGHT, STYLE_VAL_AUTO);
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