#include "style.h"
#include <limits>

using namespace oak::ui;
using namespace oak::style;

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

  for (uint i=0; i<attrs.size(); i++)
  {
    attrs[i] = NULL_ATTR;
  }
}

void Style::setPadding(float x, float y)
{
  attrs[padding_left] = x;
  attrs[padding_right] = x;
  attrs[padding_top] = y;
  attrs[padding_bottom] = y;
}

void Style::setMargin(float x, float y)
{
  attrs[margin_left] = x;
  attrs[margin_right] = x;
  attrs[margin_top] = y;
  attrs[margin_bottom] = y;
}

