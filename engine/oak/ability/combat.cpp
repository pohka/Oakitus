#include <oak/ability/combat.h>
#include <oak/time/time.h>
#include <sstream>

using namespace oak;

std::vector<CombatLog> Combat::entryBacklog;
std::vector<CombatEntry> Combat::recentEntrys;

std::string CombatLog::toString()
{
  std::string str = "";
  if (entryType == Combat::ENTRY_TYPE_DAMAGE)
  {
    str += giverName + " hits " + receiverName + " for " + std::to_string(amount) + " damage (" + std::to_string(startingHP) + "->" + std::to_string(startingHP - amount) + ")";
  }
  else if (entryType == Combat::ENTRY_TYPE_HEAL)
  {
    str += giverName + " heals " + receiverName + " for " + std::to_string(amount) + " health (" + std::to_string(startingHP) + "->" + std::to_string(startingHP + amount) + ")";
  }
  return str;
}

void Combat::applyDamage(
  Unit* victim,
  Unit* attacker,
  int amount,
  Ability* ability,
  unsigned char elementType
)
{
  recentEntrys.push_back({
    ENTRY_TYPE_DAMAGE,
    victim,
    attacker,
    amount,
    ability,
    elementType
  });
}

void Combat::applyHeal(
  Unit* receiver,
  Unit* giver,
  int amount,
  Ability* ability,
  unsigned char elementType
)
{
  recentEntrys.push_back({
    ENTRY_TYPE_DAMAGE,
    receiver,
    giver,
    amount,
    ability,
    elementType
  });
}

void Combat::init()
{
  entryBacklog.reserve(BACKLOG_MAXSIZE);
}

void Combat::onTick()
{
  const float now = Time::getGameTime();
  for (auto it : recentEntrys)
  {
    //do entry actions
    if (it.receiver->getIsAlive())
    {
      int startingHP = it.receiver->getHealth();
      int diff = 0;
      
      //damage
      if (it.entryType == ENTRY_TYPE_DAMAGE)
      {
        int endingHP = startingHP - it.amount; //todo: take into account modifiers
        if (endingHP <= 0)
        {
          endingHP = 0;
          //todo: add to kill list
        }
        it.receiver->setHealth(endingHP);
        diff = startingHP - endingHP;
      }
      //heal
      else if (it.entryType == ENTRY_TYPE_HEAL)
      {
        it.receiver->heal(it.amount);
        diff = it.receiver->getHealth() - startingHP;
      }
    

      //remove oldest backlog entry if max size has been reached
      if (entryBacklog.size() >= BACKLOG_MAXSIZE)
      {
        entryBacklog.erase(entryBacklog.begin());
      }
      entryBacklog.push_back({
        it.giver->getName(),
        it.receiver->getName(),
        it.ability->getName(),
        diff,
        it.entryType,
        startingHP,
        now
      });
    }
  }
  recentEntrys.clear();
}