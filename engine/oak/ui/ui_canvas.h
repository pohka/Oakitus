#ifndef UI_CANVAS_H
#define UI_CANVAS_H



#include <map>
#include <oak/core/types.h>

#include "../core/window.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H  

#include "ui_character.h"
#include "ui_node.h"
#include "ui_component.h"
#include "style.h"
#include "ui_point.h"

namespace ion
{
  ///container for all of the ui
  class UICanvas
  {
    public:
      friend class StyleLoader;

      friend class oak::Window;
      ///called when the window is resized
      static void onWindowResize(float windowToVPRatioX, float windowToVPRatioY);
      ///renders all the components
      static void render();
      ///Projection from pixel units to viewport coords to window coords
      static const UIPoint& getProjection();
      ///add a ui component
      static void addComponent(ushort id, UIComponent* component);
      ///returns a component by id
      static UIComponent* getComponent(ushort id);

      //find a style by selector, nullptr returned if not found
      static Style* findStyle(std::string selector);

      //add a style, note: state styles will be deleted if the selector is not parsed correctly
      static void addStyle(Style* style);

      static UINode* focusedNode;

    private:
      static void deleteAllStyles();
      static UIPoint projection; //current projection
      static std::map<ushort, UIComponent*> components; //all if the existing components
      static std::vector<Style*> styles;
      
  };
}

#endif