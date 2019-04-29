#pragma once
#ifndef OAKITUS_H
#define OAKITUS_H

#include "types.h"

namespace oak
{
  //Engine
  class Oakitus
  {
    
    public:
      //Initalize the engine
      static void init();
      
    private:

      //Called before the game loop to load the game
      static void load();

      //Starts the game loop
      static int loop();
      
  };
}

#endif