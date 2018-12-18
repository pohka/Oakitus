#ifndef UI_COMPONENT_H
#define UI_COMPONENT_H

#include "ui_def.h"
#include <vector>
#include "ui_node.h"
#include <core/point.h>
#include "localization.h"

namespace oak
{
  namespace ui
  {
    ///a container for UI nodes
    struct UIComponent
    {
      
      Point align = { 
        UI_ALIGN_HORZ_LEFT, 
        UI_ALIGN_VERT_TOP 
      };
      Point offset = { 0,0 };
      Point absolutePos = {};
      virtual void onBeforeRender() = 0;

      void render(oak::Point& projection)
      {
        absolutePos.x = (offset.x * projection.x) + align.x;
        absolutePos.y = (offset.y * projection.y) + align.y;
        for (UINode* node : nodes)
        {
          node->render();
        }
      }

      void onWindowResize(float windowToVPRatioX, float windowToVPRatioY)
      {
        for (UINode* node : nodes)
        {
          node->onWindowResize(windowToVPRatioX, windowToVPRatioY);
        }
      }

      void addNode(UINode* node)
      {
        node->setComponent(this);
        nodes.push_back(node);
      }

      private:
        std::vector<UINode*> nodes;
    };
  }
}

#endif