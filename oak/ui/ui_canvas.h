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
#include "style.h"



namespace oak
{
  namespace ui
  {
    ///container for all of the ui
    class UICanvas
    {
      public:
        friend class oak::Window;
        ///called when the window is resized
        static void onWindowResize(float windowToVPRatioX, float windowToVPRatioY);
        ///renders all the components
        static void render();
        ///Projection from pixel units to viewport coords to window coords
        static const oak::Point& getProjection(); 
        ///add a ui component
        static void addComponent(ushort id, UIComponent* component);
        ///returns a component by id
        static UIComponent* getComponent(ushort id);

        static Style* findStyle(std::string cls);

        static void addStyle(Style* style);

    private:
        static oak::Point projection; //current projection
        static std::map<ushort, UIComponent*> components; //all if the existing components
        static std::vector<Style*> styles;
    };

    
  }
}

#endif