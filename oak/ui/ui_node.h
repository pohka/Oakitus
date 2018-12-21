#ifndef UI_NODE_H
#define UI_NODE_H

#include "../core/types.h"
#include "ui_def.h"
#include <core/point.h>
#include <vector>
#include <core/point.h>
#include "style.h"
//#include "color.h"

namespace ion
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
      
    oak::Point pos = { 0,0 };
      
    std::string id = "";
      
    uchar positionType = UI_POSITION_RELATIVE;
    UIRect rect;

    virtual void render(oak::Point& nodeCursor) = 0;
    virtual void onWindowResize(float windowToVPRatioX, float windowToVPRatioY) = 0;

    void setComponent(UIComponent* component);
    void addChild(UINode* node);
    UINode* getParent();
    uchar getType();
    bool getIsRootNode();
    oak::Point& getParentPos();

    void addClass(std::string cssClass);
    void calcStyle();
      

    //void update();

    //void(*onClick)(UINode*) = nullptr;
    void (*onFocus)(UINode*) = nullptr;
      
    std::vector<UINode*> children;
    Style* style; //inline css

    float getTotalH();

  protected:
    UINode* parent = nullptr;
    uchar nodeType;
    UIComponent* component;
    std::vector<std::string> classList;
    Style* cstyle; //computed style

    //if an attr with a matching key exists,
    //then the attr value is appended to the val argument
    void app(float& val, uchar key);
      

    void renderBegin(oak::Point& nodeCursor);
    void renderEnd(oak::Point& nodeCursor);
      


  private:
    bool isRootNode = true;
    void mutateComputedStyle(Style* style);
    float totalW = 0.0f;
    float totalH = 0.0f;

  };
}

#endif