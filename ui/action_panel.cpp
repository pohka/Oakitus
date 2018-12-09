#include "action_panel.h"
#include <ui/ui_image.h>
#include <ui/ui_label.h>

using namespace game::ui;
using namespace oak::ui;

ActionPanel::ActionPanel()
{
  align.x = UI_ALIGN_HORZ_LEFT;
  align.y = UI_ALIGN_VERT_BOTTOM;

  UINode* img = UIImage::createImage("action_panel.png", 440, 64);
  img->offset.x = 220.0f;
  img->offset.y = 45.0f;
  nodes.push_back(img);

  UILabel* label = UILabel::createLabel("HP: 100", 20, 400, 20);
  label->color = { 0.9f, 0.9f, 0.9f };
  label->offset.x = 30.0f;
  label->offset.y = 60.0f;
  nodes.push_back(label);
}