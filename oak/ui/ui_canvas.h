#ifndef UI_CANVAS_H
#define UI_CANVAS_H



#include <map>
#include <core/types.h>

#include "../core/window.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H  

#include "ui_character.h"
#include "ui_node.h"
#include "ui_component.h"
#include <core/point.h>



namespace oak
{
  namespace ui
  {
    class UICanvas
    {
      public:
        friend class oak::Window;

        static void onWindowResize(float windowToVPRatioX, float windowToVPRatioY);
        static void render();
        static const oak::Point& getProjection();
        static void addComponent(ushort id, UIComponent* component);
        static UIComponent* getComponent(ushort id);

    private:
        static oak::Point projection;
        static std::map<ushort, UIComponent*> components;
    };

    
  }
}

#endif