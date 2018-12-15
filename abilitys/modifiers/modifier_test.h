#ifndef MODIFIER_TEST_H
#define MODIFIER_TEST_H

#include "../../systems/modifier.h"

namespace game
{
  struct ModifierTest : public Modifier
  {
    ModifierTest();
    void onCreated() override;
  };
}

#endif