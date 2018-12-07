#ifndef UI_CANVAS_H
#define UI_CANVAS_H



#include <vector>
#include <core/types.h>

#include "../core/window.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H  

#include "ui_character.h"
#include "ui_node.h"


namespace oak
{
  namespace ui
  {
    class UICanvas
    {
      public:
        friend class oak::Window;

        static std::vector<UINode*> nodes;

        static void onWindowResize(float windowToVPRatioX, float windowToVPRatioY);
        static void init();
        static void render();

    private:
      
      static void initChars(FT_Library& ft, FT_Face& face);

      
    };
  }
}

#endif