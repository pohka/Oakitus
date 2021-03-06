#pragma once
#ifndef UI_COMPONENT_H
#define UI_COMPONENT_H

#include "ui_def.h"
#include <vector>
#include "ui_node.h"
#include "ui_point.h"
#include <oak/window/window.h>

namespace ion
{
  //a container for UI nodes
  struct UIWidget
  {
      
    UIPoint align = {
      UI_ALIGN_HORZ_LEFT, 
      UI_ALIGN_VERT_TOP 
    };
    UIPoint offset;
    UIPoint pos;
    UIPoint margin;
    UIPoint padding;

    ~UIWidget();

    virtual void onBeforeRender() = 0;

    void render(UIPoint& projection);

    void onWindowResize(float windowToVPRatioX, float windowToVPRatioY);

    void addNode(UINode* node);

    void recomputeStyle();

  protected:
    UINode* findNodeByID(std::string id);

    private:
      std::vector<UINode*> nodes;
  };
}

#endif