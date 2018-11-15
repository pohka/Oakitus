#ifndef KEYOBJ_H
#define KEYOBJ_H
#include "key_code.h"

namespace oak
{
  class Key
  {
    KeyCode code;
    bool isDown;
    bool lastIsDown;

    public:
      friend class Input;
      Key(KeyCode code);
      ~Key();
      KeyCode getCode();

    private:
      void setState(bool isDown);

  };
}

#endif