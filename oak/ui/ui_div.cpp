#include "ui_div.h"

using namespace ion;

UIDiv::UIDiv() : UINode(UI_NODE_DIV)
{

}

UIDiv::~UIDiv()
{

}

void UIDiv::render(UIPoint& nodeCursor)
{
  UINode::renderBegin(nodeCursor);
  UINode::renderEnd(nodeCursor);
}

void UIDiv::onWindowResize(float windowToVPRatioX, float windowToVPRatioY)
{

}