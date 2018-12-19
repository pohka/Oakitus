#include "ui_div.h"

using namespace oak::ui;

UIDiv::UIDiv() : UINode(UI_NODE_DIV)
{

}

UIDiv::~UIDiv()
{

}

void UIDiv::render()
{
  UINode::updatePos();
  UINode::render();
}

void UIDiv::onWindowResize(float windowToVPRatioX, float windowToVPRatioY)
{

}