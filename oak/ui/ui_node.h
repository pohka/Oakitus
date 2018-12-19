#ifndef UI_NODE_H
#define UI_NODE_H

#include "../core/types.h"
#include "ui_def.h"
#include <core/point.h>
#include <vector>

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


      virtual void render();
      virtual void onWindowResize(float windowToVPRatioX, float windowToVPRatioY) = 0;

      void setComponent(UIComponent* component);
      void addChild(UINode* node);
      UINode* getParent();
      uchar getType();
      bool getIsRootNode();
      Point& getParentPos();
      uint childCount();
      
      std::vector<UINode*> children;

    protected:
      
      UINode* parent = nullptr;
      uchar nodeType;
      UIComponent* component;

      void updatePos();

    private:
      bool isRootNode = true;
    };
  }
}

#endif