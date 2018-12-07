#ifndef UI_CANVAS_H
#define UI_CANVAS_H

#include <vector>
#include <core/types.h>
#include <ui/ui_def.h>

namespace oak
{
  namespace ui
  {
    struct UIElement
    {
      std::vector<UIElement*> children;
      uchar alignment = UI_ALIGN_MIDDLE_CENTER;
      short x = 0;
      short y = 0;
      ushort w = 1;
      ushort h = 1;
    };

    struct UIImage
    {
      std::string src;
      uint VAO, VBO;
      uint textureID;
      float x = 0;
      float y = 0;
      ushort w;
      ushort h;
    };

    class UICanvas
    {
      static std::vector<UIElement*> elements;
      

      public:
        static std::vector<UIImage*> imgs;

        static void render();
        static void addElement(UIElement* element);
        static UIImage* createImage(std::string src, ushort w, ushort h);
        static void renderImage(UIImage* img);
        static void removeImage(UIImage* img);
    };
  }
}

#endif