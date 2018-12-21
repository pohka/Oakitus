#include "ui_node.h"
#include "ui_component.h"
#include "ui_canvas.h"
#include <core/input.h>
#include <debug.h>

using namespace oak::ui;
using namespace oak;

UINode::UINode(const uchar nodeType)
{
  this->nodeType = nodeType;
  cstyle = new Style("");
  style = new Style("self");
}

UINode::~UINode()
{
  for (uint i = 0; i < children.size(); i++)
  {
    delete children[i];
  }
  children.clear();
}

void UINode::setComponent(UIComponent* component)
{
  this->component = component;
}

void UINode::addChild(UINode* node)
{
  node->calcStyle();
  node->parent = this;
  node->isRootNode = false;
  node->component = component;
  children.push_back(node);
}

UINode* UINode::getParent()
{
  return parent;
}

uchar UINode::getType()
{
  return nodeType;
}

bool UINode::getIsRootNode()
{
  return isRootNode;
}

Point& UINode::getParentPos()
{
  if (isRootNode)
  {
    return component->pos;
  }
  else
  {
    return parent->pos;
  }
}

float UINode::getTotalH()
{
  return totalH;
}

void UINode::renderEnd(Point& nodeCursor)
{
  Point childCursor = { nodeCursor.x, nodeCursor.y };


  totalW = 0.0f;
  app(totalW, STYLE_MARGIN_LEFT);
  app(totalW, STYLE_MARGIN_RIGHT);

  float width = cstyle->get(STYLE_WIDTH);
  if (width != STYLE_VAL_AUTO)
  {
    totalW += width;
  }

  totalH = 0.0f;
  app(totalH, STYLE_MARGIN_TOP);
  app(totalH, STYLE_MARGIN_BOTTOM);

  //total size of all the child nodes
  Point childrenTotalSize = {};

  //calculate total height if automatic height
  float height = cstyle->get(STYLE_HEIGHT);
  if (height == STYLE_VAL_AUTO)
  {
    for (auto node : children)
    {
      node->render(childCursor);
      if (node->positionType == UI_POSITION_RELATIVE)
      {
        float childNodeH = node->getTotalH();
        childCursor.y -= childNodeH;
        childrenTotalSize.y += childNodeH;
      }
    }
    totalH += childrenTotalSize.y;
  }
  else
  {
    totalH += height;

    for (auto node : children)
    {
      node->render(childCursor);
      if (node->positionType == UI_POSITION_RELATIVE)
      {
        float childNodeH = node->getTotalH();
        childCursor.y -= childNodeH;
        childrenTotalSize.y += childNodeH;
      }
    }
  }

  if (Input::hasMouseMoved())
  {
    glm::vec2 windowUnit = Window::getWindowUnitToPixel();
    rect.x = nodeCursor.x;
    rect.y = nodeCursor.y;
    rect.w = 200.0f; //todo auto width
    //app(rect.w, STYLE_WIDTH);
    //app(rect.w, STYLE_PADDING_LEFT);
    //app(rect.w, STYLE_PADDING_RIGHT);
    //  cstyle->attrs[style::width] +
    //  cstyle->attrs[style::padding_left] +
    //  cstyle->attrs[style::padding_right];
    rect.h = 0.0f;
    if (height == STYLE_VAL_AUTO)
    {
      rect.h = childrenTotalSize.y;
    }
    else
    {
      app(rect.h, STYLE_HEIGHT);
    }
    app(rect.h, STYLE_PADDING_TOP);
    app(rect.h, STYLE_PADDING_BOTTOM);

    float xx = (Input::mousePos.x - Window::getWidth() / 2.0f) / Window::getWindowToVPRatio().x;
    float yy = (Input::mousePos.y - Window::getHeight() / 2.0f) / Window::getWindowToVPRatio().y;

    if (onFocus != nullptr)
    {
      LOG << "rect:" << rect.x << "," << rect.y << "," << rect.w << "," << rect.h;
      LOG << "mouse:" << xx << "," << yy;
    }

    
    if (rect.containsPt(xx, yy))
    {
      if (onFocus != nullptr)
      {
        LOG << "contains pt";
        onFocus(this);
      }
    }
  }

  Point padding = {};
  app(padding.x, STYLE_PADDING_LEFT);
  app(padding.y, STYLE_PADDING_TOP);

  Point margin = {};
  app(margin.x, STYLE_MARGIN_LEFT);
  app(margin.y, STYLE_MARGIN_TOP);

  nodeCursor.x -= padding.x + margin.x;
  nodeCursor.y -= -padding.y - margin.y;
}

void UINode::renderBegin(Point& nodeCursor)
{
  Point parentPos = getParentPos();
  pos.x = parentPos.x;
  pos.y = parentPos.y;

  Point padding = {};
  app(padding.x, STYLE_PADDING_LEFT);
  app(padding.y, STYLE_PADDING_TOP);
  

  Point margin = {};
  app(margin.x, STYLE_MARGIN_LEFT);
  app(margin.y, STYLE_MARGIN_TOP);

  nodeCursor.x += padding.x + margin.x;
  nodeCursor.y += -padding.y - margin.y;
}

void UINode::addClass(Style* style)
{
  cstyle->classList.push_back(style->classList[0]);
}

void UINode::calcStyle()
{
  for (std::string cls : cstyle->classList)
  {
    Style* style = UICanvas::findStyle(cls);
    if (style != nullptr)
    {
      mutateComputedStyle(style);
    }
  }

  mutateComputedStyle(style);
  //set to default font size if font is auto
  float fontSize = cstyle->get(STYLE_FONT_SIZE);
  if (fontSize == STYLE_VAL_AUTO)
  {
    cstyle->set(STYLE_FONT_SIZE, STYLE_DEFAULT_FONT_SIZE);
  }
}

void UINode::mutateComputedStyle(Style* style)
{
  if (cstyle->position < style->position)
  {
    cstyle->position = style->position;
  }

  //color is not null
  if (style->color.a >= 0.0f)
  {
    cstyle->color = style->color;
  }

  for (uint i = 0; i < style->attrs.size(); i++)
  {
    //negative values are used
    if (style->attrs[i] != STYLE_VAL_AUTO)
    {
      cstyle->attrs[i] = style->attrs[i];
    }
  }
}

void UINode::app(float& val, uchar key)
{
  float cVal = cstyle->get(key);
  if (cVal != STYLE_VAL_AUTO)
  {
    val += cVal;
  }
}