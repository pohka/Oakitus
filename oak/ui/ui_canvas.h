#ifndef UI_CANVAS_H
#define UI_CANVAS_H



#include <vector>
#include <core/types.h>
#include <ui/ui_def.h>
#include <core/window.h>

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
      std::string text = "abc";
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
        friend class oak::Window;
        friend class oak::Oakitus;

        static std::vector<UIImage*> imgs;

        
        static void addElement(UIElement* element);
        static UIImage* createImage(std::string src, ushort w, ushort h);
        static void renderImage(UIImage* img);
        static void removeImage(UIImage* img);
        static void renderElement(UIElement* element);

    private:
      static void render();
      static void init();
      static void setImageBuffer(
        UIImage* img, 
        float windowToVPRatioX, 
        float windowToVPRatioY
      );

      static void onWindowResize(float windowToVPRatioX, float windowToVPRatioY);
    };
  }
}

#endif