#ifndef MOVE_SCRIPT_H
#define MOVE_SCRIPT_H

#include "Script.h"

namespace oak
{
  class MoveScript : public Script
  {
    public:
      MoveScript();
      ~MoveScript();
      void onUpdate() override;
  };
}

#endif