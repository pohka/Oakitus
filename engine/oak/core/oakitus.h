#ifndef OAKITUS_H
#define OAKITUS_H

#include "types.h"

namespace oak
{
  ///<summary>Engine</summary>
  class Oakitus
  {
    
    public:
      ///<summary>Initalize the engine</summary>
      static void init();
      
    private:

      ///<summary>Called before the game loop to load the game</summary>
      static void load();

      ///<summary>Starts the game loop</summary>
      static int loop();
      
  };
}

#endif