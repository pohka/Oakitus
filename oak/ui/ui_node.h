#ifndef UI_NODE_H
#define UI_NODE_H

#include "../core/types.h"
#include "ui_def.h"
#include <core/point.h>
#include <vector>
#include <core/point.h>
//#include "color.h"

namespace oak
{
  namespace ui
  {
    struct UIComponent;

    ///a ui node which
    struct UINode
    {
      UINode(const uchar nodeType);
      ~UINode();

      Point offset = { 0,0 };
      ushort w;
      ushort h;
      Point pos = { 0,0 };
      Point margin = { 0,0 };
      Point padding = { 0,0 };
     // Color bgColor = { 0.0f, 0.0f, 0.0f, 0.0f };

      virtual void render(Point& nodeCursor) = 0;
      virtual void onWindowResize(float windowToVPRatioX, float windowToVPRatioY) = 0;

      void setComponent(UIComponent* component);
      void addChild(UINode* node);
      UINode* getParent();
      uchar getType();
      bool getIsRootNode();
      Point& getParentPos();
      
      std::vector<UINode*> children;

    protected:
      UINode* parent = nullptr;
      uchar nodeType;
      UIComponent* component;

      void renderBegin(Point& nodeCursor);
      void renderEnd(Point& nodeCursor);

    private:
      bool isRootNode = true;
    };
  }
}

#endif