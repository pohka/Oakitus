#ifndef KEYOBJ_H
#define KEYOBJ_H
#include "key_code.h"

namespace oak
{
  ///<summary>Key buffer that tracks the input for a key</summary>
  class KeyBuffer
  {
    KeyCode code;
    bool isDown;
    bool lastIsDown;

    public:
      friend class Input;
      KeyBuffer(KeyCode code);
      ~KeyBuffer();
      ///<summary>Returns the KeyCode of this key</summary>
      KeyCode getCode() const;

    private:
      ///<summary>Set the captured state for the key for this frame</summary>
      void setState(bool isDown);

  };
}

#endif