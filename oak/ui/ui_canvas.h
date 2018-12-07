#ifndef UI_CANVAS_H
#define UI_CANVAS_H



#include <vector>
#include <core/types.h>
#include <ui/ui_def.h>
#include <core/window.h>
#include <map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H  



namespace oak
{
  namespace ui
  {
    struct Color
    {
      float r = 0.0f;
      float g = 0.0f;
      float b = 0.0f;
    };

    struct UINode
    {
      uchar nodeType;
      float x = 0;
      float y = 0;
      ushort w;
      ushort h;
    };

    struct UILabel : public UINode
    {
      UILabel()
      {
        nodeType = UI_NODE_LABEL;
      }

      std::string text;
      float scale = 1.0f;
      uint VAO, VBO;
      Color color;
    };

    struct UIImage : public UINode
    {
      UIImage()
      {
        nodeType = UI_NODE_IMAGE;
      }
      std::string src;
      uint VAO, VBO;
      uint textureID;
    };

    struct Character
    {
      GLuint     textureID;  // ID handle of the glyph texture
      glm::ivec2 size;       // Size of glyph
      glm::ivec2 bearing;    // Offset from baseline to left/top of glyph
      GLuint     advance;    // Offset to advance to next glyph
    };

    class UICanvas
    {
      //static std::vector<UIElement*> elements;


      static std::map<GLchar, Character> characters;
      

      public:
        friend class oak::Window;
        friend class oak::Oakitus;

        static std::vector<UINode*> nodes;

        static UIImage* createImage(std::string src, ushort w, ushort h);
        static UILabel* createLabel(std::string src, ushort w, ushort h);
        static void renderImage(UIImage* img);
        static void removeImage(UIImage* img);
        static void renderLabel(UILabel* label);

    private:
      static void render();
      static void init();
      static void initChars(FT_Library& ft, FT_Face& face);
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