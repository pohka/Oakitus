#ifndef COMBAT_H
#define COMBAT_H

#include <vector>
#include <string>
#include <oak/components/unit.h>

namespace oak
{
  struct CombatLog
  {
    char entryType;
    Unit* receiver;
    Unit* giver;
    int amount;
    Ability* ability;
    unsigned char elementType;
  };

  struct CombatLogResult
  {
    std::string giverName;
    std::string receiverName;
    std::string abilityName;
    int amount;
    char entryType;
    int beginHP;
    int endHP;
    float time;

    std::string toString();
  };

  class Combat
  {
  public:
    static const unsigned int BACKLOG_MAXSIZE = 50;

    static void log(
      char entryType,
      Unit* victim,
      Unit* attacker,
      int amount,
      Ability* ability,
      unsigned char elementType
    );

    static void init();
    static void onTick();

    static const char ENTRY_TYPE_DAMAGE = 0;
    static const char ENTRY_TYPE_HEAL = 1;

  private:
    static std::vector<CombatLogResult> backlog;
    static std::vector<CombatLog> recentLogs;

    static void applyLog(CombatLog& data);
    static void addBacklog(CombatLog& data, int beginHP);
  };
}

#endif