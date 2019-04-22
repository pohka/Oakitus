#ifndef COMBAT_H
#define COMBAT_H

#include <vector>
#include <string>
#include <oak/components/unit.h>

namespace oak
{
  struct CombatEntry
  {
    char entryType;
    Unit* receiver;
    Unit* giver;
    int amount;
    Ability* ability;
    unsigned char elementType;
  };

  struct CombatLog
  {
    std::string giverName;
    std::string receiverName;
    std::string abilityName;
    int amount;
    char entryType;
    int startingHP;
    float time;

    std::string toString();
  };

  class Combat
  {
  public:
    static const unsigned int BACKLOG_MAXSIZE = 50;

    static void applyDamage(
      Unit* victim,
      Unit* attacker,
      int amount,
      Ability* ability,
      unsigned char elementType
    );

    static void applyHeal(
      Unit* receiver,
      Unit* giver,
      int amount,
      Ability* ability,
      unsigned char elementType
    );

    static void init();
    static void onTick();

    static const char ENTRY_TYPE_DAMAGE = 0;
    static const char ENTRY_TYPE_HEAL = 1;

  private:
    static std::vector<CombatLog> entryBacklog;
    static std::vector<CombatEntry> recentEntrys;

    
  };
}

#endif