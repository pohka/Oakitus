#ifndef UI_COMPONENT_H
#define UI_COMPONENT_H

#include "ui_def.h"
#include <vector>
#include "ui_node.h"
#include "ui_point.h"
#include "localization.h"
#include <core/window.h>

namespace ion
{
  ///a container for UI nodes
  struct UIComponent
  {
      
    UIPoint align = {
      UI_ALIGN_HORZ_LEFT, 
      UI_ALIGN_VERT_TOP 
    };
    UIPoint offset;
    UIPoint pos;
    UIPoint margin;
    UIPoint padding;

    virtual void onBeforeRender() = 0;

    void render(UIPoint& projection);

    void onWindowResize(float windowToVPRatioX, float windowToVPRatioY);

    void addNode(UINode* node);

    void recomputeStyle();

    private:
      std::vector<UINode*> nodes;
  };
}

#endif