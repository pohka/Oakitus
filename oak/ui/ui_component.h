#ifndef UI_COMPONENT_H
#define UI_COMPONENT_H

#include "ui_def.h"
#include <vector>
#include "ui_node.h"
#include <core/point.h>
#include "localization.h"
#include <core/window.h>

namespace ion
{
  ///a container for UI nodes
  struct UIComponent
  {
      
    oak::Point align = { 
      UI_ALIGN_HORZ_LEFT, 
      UI_ALIGN_VERT_TOP 
    };
    oak::Point offset = { 0,0 };
    oak::Point pos = { 0,0 };
    oak::Point margin = { 0,0 };
    oak::Point padding = { 0,0 };

    virtual void onBeforeRender() = 0;

    void render(oak::Point& projection);

    void onWindowResize(float windowToVPRatioX, float windowToVPRatioY);

    void addNode(UINode* node);

    private:
      std::vector<UINode*> nodes;
  };
}

#endif