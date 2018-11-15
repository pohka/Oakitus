#ifndef MOVE_SCRIPT_H
#define MOVE_SCRIPT_H

#include "core/Script.h"

namespace game
{
  class MoveScript : public oak::Script
  {
    public:
      MoveScript();
      ~MoveScript();
      void onUpdate() override;
  };
}

#endif