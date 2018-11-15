#ifndef COMPONENT_H
#define COMPONENT_H

class Entity;

class Component
{
  friend class Entity;
  unsigned int componentID;

  public:
    Component();
    virtual ~Component();
    static unsigned int getNextID();
    virtual void onUpdate();
    virtual void onDraw();

  protected:
    Entity* entity;

};

#endif