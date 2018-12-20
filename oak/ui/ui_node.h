#ifndef UI_NODE_H
#define UI_NODE_H

#include "../core/types.h"
#include "ui_def.h"
#include <core/point.h>
#include <vector>
#include <core/point.h>
#include "style.h"
//#include "color.h"

namespace oak
{
  namespace ui
  {
    struct UIComponent;

    struct UIRect
    {
      float x, y, w, h;

      bool containsPt(float ptX, float ptY)
      {
        return (ptX >= x && ptX <= x + w  && ptY <= y && ptY >= y - h);
      }
    };

    ///a ui node which
    struct UINode
    {
      UINode(const uchar nodeType);
      ~UINode();

      Point offset = { 0,0 };
      ushort w = 0;
      ushort h = 0;
      Point pos = { 0,0 };
      Point margin = { 0,0 };
      Point padding = { 0,0 };
      
      std::string id = "";
      
      
     // Color bgColor = { 0.0f, 0.0f, 0.0f, 0.0f };
      bool isAutoH = true;
      bool isAutoW = true;
      uchar positionType = UI_POSITION_RELATIVE;
      UIRect rect;

      virtual void render(Point& nodeCursor) = 0;
      virtual void onWindowResize(float windowToVPRatioX, float windowToVPRatioY) = 0;

      void setComponent(UIComponent* component);
      void addChild(UINode* node);
      UINode* getParent();
      uchar getType();
      bool getIsRootNode();
      Point& getParentPos();

      void addClass(Style* style);

      //void update();

      //void(*onClick)(UINode*) = nullptr;
      void (*onFocus)(UINode*) = nullptr;
      
      std::vector<UINode*> children;

      ushort getTotalH();

    protected:
      UINode* parent = nullptr;
      uchar nodeType;
      UIComponent* component;
      std::vector<std::string> classList;
      Style* computedStyle;

      void renderBegin(Point& nodeCursor);
      void renderEnd(Point& nodeCursor);
      


    private:
      bool isRootNode = true;

    };
  }
}

#endif