#ifndef MODIFIER_TEST_H
#define MODIFIER_TEST_H

#include "../../systems/modifier.h"

namespace game
{
  struct ModifierTest : public Modifier
  {

    void onCreated() override;
  };
}

#endif