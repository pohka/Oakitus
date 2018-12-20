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
  computedStyle = new Style("");
  //default style
  computedStyle->attrs[style::font_size] = 20.0f;
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

ushort UINode::getTotalH()
{
  return (ushort)(margin.y * 2) + h;
}

void UINode::renderEnd(Point& nodeCursor)
{
  Point childCursor = { nodeCursor.x, nodeCursor.y };

  //calculate total height if automatic height
  if (isAutoH)
  {
    //margin and padding
    //h += (ushort)(margin.y + padding.y) * 2;

    for (auto node : children)
    {
      node->render(childCursor);
      if (node->positionType == UI_POSITION_RELATIVE)
      {
        ushort childNodeH = node->getTotalH();
        childCursor.y -= childNodeH;
        h += childNodeH; //height of each child node
      }
    }
    //h = totalH;
  }
  else
  {
    for (auto node : children)
    {
      node->render(childCursor);
      if (node->positionType == UI_POSITION_RELATIVE)
      {
        childCursor.y -= node->getTotalH();
      }
    }
  }

  if (Input::hasMouseMoved())
  {
    glm::vec2 windowUnit = Window::getWindowUnitToPixel();
    rect.x = nodeCursor.x;// +windowUnit.x;
    rect.y = nodeCursor.y;
    rect.w = (float)w + padding.x * 2.0f;
    rect.h = (float)h + padding.y * 2.0f;

    float xx = (Input::mousePos.x - Window::getWidth() / 2.0f) / Window::getWindowToVPRatio().x;
    float yy = (Input::mousePos.y - Window::getHeight() / 2.0f) / Window::getWindowToVPRatio().y;

    if (onFocus != nullptr)
    {
     // LOG << "windowUnit:" << windowUnit.x << "," << windowUnit.y;
      LOG << "rect:" << rect.x << "," << rect.y << "," << rect.w << "," << rect.h;
      LOG << "mouse:" << xx << "," << yy;
      //onFocus(this);
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

  nodeCursor.x -= offset.x + padding.x + margin.x;
  nodeCursor.y -= offset.y - padding.y - margin.y;
}

void UINode::renderBegin(Point& nodeCursor)
{
  Point parentPos = getParentPos();
  pos.x = parentPos.x + offset.x;
  pos.y = parentPos.y + offset.y;

  nodeCursor.x += offset.x + padding.x + margin.x;
  nodeCursor.y += offset.y - padding.y - margin.y;
}

void UINode::addClass(Style* style)
{
  computedStyle->classList.push_back(style->classList[0]);

  if (computedStyle->position < style->position)
  {
    computedStyle->position = style->position;
  }

  //color is not null
  if (style->color.a >= 0.0f)
  {
    computedStyle->color = style->color;
  }

  for (uint i = 0; i < style->attrs.size(); i++)
  {
    //negative values are used
    if (style->attrs[i] != Style::NULL_ATTR)
    {
      computedStyle->attrs[i] = style->attrs[i];
    }
  }
}