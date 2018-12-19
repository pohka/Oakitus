#ifndef UI_COMPONENT_H
#define UI_COMPONENT_H

#include "ui_def.h"
#include <vector>
#include "ui_node.h"
#include <core/point.h>
#include "localization.h"
#include <core/window.h>

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
      Point pos = { 0,0 };
      Point margin = { 0,0 };
      Point padding = { 0,0 };

      virtual void onBeforeRender() = 0;

      void render(oak::Point& projection)
      {
        glm::vec2 windowUnit = Window::getWindowUnitToPixel();

        pos.x = offset.x + (align.x * windowUnit.x);
        pos.y = offset.y + (align.y * windowUnit.y);

        Point nodeCursor = { 
          pos.x + margin.x + padding.x,
          pos.y + margin.y + padding.y 
        };

        for (UINode* node : nodes)
        {
          node->render(nodeCursor);
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