#ifndef MOD_EXAMPLE_H
#define MOD_EXAMPLE_H

#include "../../systems/modifier.h"

namespace game
{
  struct mod_Example : public Modifier
  {
    mod_Example();
    void onCreated() override;
  };
}

#endif