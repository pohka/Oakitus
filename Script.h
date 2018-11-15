#ifndef SCRIPT_H
#define SCRIPT_H

namespace oak
{
  class Entity;

  class Script
  {
    unsigned int scriptID;

    friend class Entity;
    public:
      Script();
      virtual ~Script();
      virtual void onUpdate();
      virtual void init();


    protected:
      Entity* entity;

    };
}

#endif
