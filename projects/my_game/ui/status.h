#ifndef STATUS_H
#define STATUS_H

#include <oak/ui/ui_widget.h>
#include <oak/ui/ui_label.h>

namespace game
{
  //example ui component
  class Status : public ion::UIWidget
  {
    int prop_hp;
    int prop_mana;
    ion::UILabel* label;
    ion::UILabel* label2;

  public:
    Status();
    ~Status();

    //update the props before rendering
    void onBeforeRender() override;
  };
}

#endif