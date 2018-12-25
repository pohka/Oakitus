#ifndef DAMAGE_DATA_H
#define DAMAGE_DATA_H

#include <oak/event/event.h>

namespace game
{
  //event data
  struct DamageData : public oak::IEventData
  {
    float amount; //raw damage
    //used when applying damage, used for total damage after casters modifiers
    float totalAmount; 

    //element id
    uchar element;

    //id of the unit giving the damage
    uint casterID;

    //id of the unit recieving the damage
    uint victimID;
  };
}

#endif