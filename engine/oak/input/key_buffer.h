#pragma once
#ifndef KEYOBJ_H
#define KEYOBJ_H
#include "key_codes.h"

namespace oak
{
  //Key buffer that tracks the input for a key
  class KeyBuffer
  {
    ushort code;
    bool isDown;
    bool lastIsDown;

    public:
      friend class Input;
      KeyBuffer(ushort  code);
      ~KeyBuffer();
      //Returns the KeyCode of this key
      ushort getCode() const;

    private:
      //Set the captured state for the key for this frame
      void setState(bool isDown);

  };
}

#endif