#include "ui_div.h"
//#include <core/point.h>

using namespace oak::ui;

UIDiv::UIDiv() : UINode(UI_NODE_DIV)
{

}

UIDiv::~UIDiv()
{

}

void UIDiv::render(oak::Point& nodeCursor)
{
  UINode::renderBegin(nodeCursor);
  UINode::renderEnd(nodeCursor);
}

void UIDiv::onWindowResize(float windowToVPRatioX, float windowToVPRatioY)
{

}