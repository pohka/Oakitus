#pragma once
#ifndef UI_DIV_H
#define UI_DIV_H

#include "ui_node.h"

namespace ion
{
  struct UIDiv : public UINode
  {
    UIDiv();
    ~UIDiv();

    void render(UIPoint& nodeCursor);
    void onWindowResize(float windowToVPRatioX, float windowToVPRatioY);
  };
}

#endif