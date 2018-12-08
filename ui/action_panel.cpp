#include "action_panel.h"
#include <ui/ui_image.h>
#include <ui/ui_label.h>

using namespace game::ui;
using namespace oak::ui;

ActionPanel::ActionPanel()
{
  alignX = UI_ALIGN_HORZ_CENTER;
  alignY = UI_ALIGN_VERT_BOTTOM;

  UINode* img = UIImage::createImage("default.png", 32, 32);
  img->x = 0.0f;
  img->y = 0.0f;
  nodes.push_back(img);

  UILabel* label = UILabel::createLabel("testing", 20, 400, 50);
  label->color = { 1.0f, 1.0f, 1.0f };
  label->y = 30;
  nodes.push_back(label);
}