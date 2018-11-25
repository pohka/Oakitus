#ifndef OAKITUS_H
#define OAKITUS_H

namespace oak
{
  class Oakitus
  {
    public:
      static void init();
      static int loop();
      static void updateEnts();
      static void drawEnts();
      static void destroyQueue();
      static void deleteAllNonGlobalEntitys();
  };
}

#endif