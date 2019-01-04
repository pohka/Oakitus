#ifndef DEBUG_INPUT_H
#define DEBUG_INPUT_H

#include <oak/build_def.h>
#ifdef DEBUG_MODE

namespace debug
{
  struct DebugInput
  {
    static void process();
  };
}

#endif

#endif
