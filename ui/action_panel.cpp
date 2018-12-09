#include "action_panel.h"
#include <ui/ui_image.h>
#include <ui/ui_label.h>

using namespace game::ui;
using namespace oak::ui;

ActionPanel::ActionPanel()
{
  alignX = UI_ALIGN_HORZ_LEFT;
  alignY = UI_ALIGN_VERT_BOTTOM;

  UINode* img = UIImage::createImage("action_panel.png", 440, 64);
  img->x = 220.0f;
  img->y = 45.0f;
  nodes.push_back(img);

  UILabel* label = UILabel::createLabel("HP: 100", 20, 400, 20);
  label->color = { 0.9f, 0.9f, 0.9f };
  label->x = 30.0f;
  label->y = 60.0f;
  nodes.push_back(label);
}