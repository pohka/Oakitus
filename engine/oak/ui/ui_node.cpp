#include "ui_node.h"
#include "ui_component.h"
#include "ui_canvas.h"
#include <oak/input/input.h>
#include <oak/debug.h>
#include <oak/input/key_codes.h>

using namespace ion;

UINode::UINode(const uchar nodeType)
{
  this->nodeType = nodeType;
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
  node->computeStyle();
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

UIPoint& UINode::getParentPos()
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

void UINode::renderEnd(UIPoint& nodeCursor)
{
  bool hasStateChanged = false;
  UIPoint childCursor = { nodeCursor.x, nodeCursor.y };


  totalW = 0.0f;
  app(totalW, STYLE_MARGIN_LEFT);
  app(totalW, STYLE_MARGIN_RIGHT);

  float width = cstyle.get(STYLE_WIDTH);
  if (width != STYLE_VAL_AUTO)
  {
    totalW += width;
  }

  totalH = 0.0f;
  app(totalH, STYLE_MARGIN_TOP);
  app(totalH, STYLE_MARGIN_BOTTOM);

  //total size of all the child nodes
  UIPoint childrenTotalSize = {};

  //calculate total height if automatic height
  float height = cstyle.get(STYLE_HEIGHT);
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

  //update focus events if the mouse has moved
  if (oak::Input::hasMouseMoved())
  {
    glm::vec2 windowUnit = oak::Window::getWindowUnitToPixel();
    rect.x = nodeCursor.x;
    rect.y = nodeCursor.y;
    rect.w = 0.0f; //todo auto width
    app(rect.w, STYLE_WIDTH);
    app(rect.w, STYLE_PADDING_LEFT);
    app(rect.w, STYLE_PADDING_RIGHT);

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

    float xx = (oak::Input::mousePos.x - oak::Window::getWidth() / 2.0f) / oak::Window::getWindowToVPRatio().x;
    float yy = (oak::Input::mousePos.y - oak::Window::getHeight() / 2.0f) / oak::Window::getWindowToVPRatio().y;
    
    //update isFocused state
    if (rect.containsPt(xx, yy))
    {
      if (state < STYLE_STATE_HOVER)
      {
        if (onMouseOver != nullptr)
        {
          onMouseOver(this);
        }
        state = STYLE_STATE_HOVER;
        hasStateChanged = true;
      }
    }
    //if point is not in rect and was previously focused
    else if (state == STYLE_STATE_HOVER)
    {
      if (onMouseLeave != nullptr)
      {
        onMouseLeave(this);
      }
      state = STYLE_STATE_NONE;
      hasStateChanged = true;
    }
  }

  if (
    state == STYLE_STATE_HOVER &&
    oak::Input::isMouseButtonDown(oak::MOUSE_BUTTON_LEFT) 
    )
  {
    if (onClick != nullptr)
    {
      onClick(this);
    }

    if (isFocusable)
    {
      //focus out current focusedNode
      if(UICanvas::focusedNode != nullptr)
      {
        UICanvas::focusedNode->state = STYLE_STATE_NONE;
        if (UICanvas::focusedNode->onFocusOut != nullptr)
        {
          UICanvas::focusedNode->onFocusOut(UICanvas::focusedNode);
        }
        UICanvas::focusedNode->computeStyle();
      }

      //focus in this node
      state = STYLE_STATE_FOCUS;
      UICanvas::focusedNode = this;
      if (onFocus != nullptr)
      {
        onFocus(this);
      }
      hasStateChanged = true;
    }
  }


  UIPoint padding = {};
  app(padding.x, STYLE_PADDING_LEFT);
  app(padding.y, STYLE_PADDING_TOP);

  UIPoint margin = {};
  app(margin.x, STYLE_MARGIN_LEFT);
  app(margin.y, STYLE_MARGIN_TOP);

  nodeCursor.x -= padding.x + margin.x;
  nodeCursor.y -= -padding.y - margin.y;

  if (hasStateChanged)
  {
    computeStyle();
  }
}

void UINode::renderBegin(UIPoint& nodeCursor)
{
  UIPoint parentPos = getParentPos();
  pos.x = parentPos.x;
  pos.y = parentPos.y;

  UIPoint padding = {};
  app(padding.x, STYLE_PADDING_LEFT);
  app(padding.y, STYLE_PADDING_TOP);
  

  UIPoint margin = {};
  app(margin.x, STYLE_MARGIN_LEFT);
  app(margin.y, STYLE_MARGIN_TOP);

  nodeCursor.x += padding.x + margin.x;
  nodeCursor.y += -padding.y - margin.y;
}

void UINode::addClass(std::string cssClass)
{
  classList.push_back(cssClass);
}

void UINode::computeStyle()
{
  for (std::string cls : classList)
  {
    if (cls.size() > 0)
    {
      Style* s = UICanvas::findStyle(cls);
      if (s!= nullptr)
      {
        mutateComputedStyle(s);

        //state style
        if (state != STYLE_STATE_NONE)
        {
          Style* stateStyle = s->findStateStyle(state);
          if (stateStyle != nullptr)
          {
            mutateComputedStyle(stateStyle);
          }
        }
      }
      else
      {
        LOG << "style class not found:" << cls;
      }
    }
  }

  mutateComputedStyle(&style); //inline style

  //set to default font size if font is auto
  float fontSize = cstyle.get(STYLE_FONT_SIZE);
  if (fontSize == STYLE_VAL_AUTO)
  {
    cstyle.set(STYLE_FONT_SIZE, STYLE_DEFAULT_FONT_SIZE);
  }

  //use default font color if not set
  if (cstyle.color == COLOR_NULL)
  {
    cstyle.color = COLOR_DEFAULT_FONT;
  }

  //recalculate child nodes
  for (uint i = 0; i < children.size(); i++)
  {
    children[i]->computeStyle();
  }
}

void UINode::mutateComputedStyle(Style* style)
{
  if (cstyle.position < style->position)
  {
    cstyle.position = style->position;
  }

  //color is not null
  if (style->color != COLOR_NULL)
  {
    cstyle.color.r = style->color.r;
    cstyle.color.g = style->color.g;
    cstyle.color.b = style->color.b;
    cstyle.color.a = style->color.a;
  }

  for (uint i = 0; i < style->attrs.size(); i++)
  {
    //negative values are used
    if (style->attrs[i] != STYLE_VAL_AUTO)
    {
      cstyle.attrs[i] = style->attrs[i];
    }
  }
}

void UINode::app(float& val, uchar key)
{
  float cVal = cstyle.get(key);
  if (cVal != STYLE_VAL_AUTO)
  {
    val += cVal;
  }
}

UINode* UINode::findNodeByID(std::string id)
{
  for (uint i = 0; i < children.size(); i++)
  {
    if (children[i]->id == id)
    {
      return children[i];
    }
    else
    {
      UINode* node = children[i]->findNodeByID(id);
      if (node != nullptr)
      {
        return node;
      }
    }
  }
  return nullptr;
}

void UINode::removeClass(std::string cssClass)
{;
  for (uint i = 0; i < classList.size(); i++)
  {
    if (classList[i] == cssClass)
    {
      classList.erase(classList.begin() + i);
      return;
    }
  }
}