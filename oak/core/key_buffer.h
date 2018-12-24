#ifndef KEYOBJ_H
#define KEYOBJ_H
#include "key_codes.h"

namespace oak
{
  ///<summary>Key buffer that tracks the input for a key</summary>
  class KeyBuffer
  {
    ushort code;
    bool isDown;
    bool lastIsDown;

    public:
      friend class Input;
      KeyBuffer(const ushort  code);
      ~KeyBuffer();
      ///<summary>Returns the KeyCode of this key</summary>
      ushort getCode() const;

    private:
      ///<summary>Set the captured state for the key for this frame</summary>
      void setState(bool isDown);

  };
}

#endif