#include <oak/ability/combat_tracker.h>
#include <oak/time/time.h>
#include <sstream>
#include <oak/core/fmath.h>
#include <cstdlib>

using namespace oak;

std::vector<CombatLogResult> CombatTracker::backlog;
std::vector<CombatLog> CombatTracker::recentLogs;

std::string CombatLogResult::toString()
{
  std::string str = "";
  if (entryType == CombatTracker::ENTRY_TYPE_DAMAGE)
  {
    str += giverName + " hits " + receiverName +
      " for " + std::to_string(amount) + " damage (" +
      std::to_string(beginHP) + "->" +
      std::to_string(beginHP - amount) + ")";
  }
  else if (entryType == CombatTracker::ENTRY_TYPE_HEAL)
  {
    str += giverName + " heals " + receiverName +
      " for " + std::to_string(amount) + " health ("
      + std::to_string(beginHP) + "->" +
      std::to_string(endHP) + ")";
  }
  return str;
}

void CombatTracker::log(
  char entryType,
  Unit* victim,
  Unit* attacker,
  int amount,
  Ability* ability,
  unsigned char elementType
)
{
  recentLogs.push_back({
    entryType,
    victim,
    attacker,
    amount,
    ability,
    elementType
  });
}

void CombatTracker::init()
{
  backlog.reserve(BACKLOG_MAXSIZE);
}

void CombatTracker::onTick()
{
  for (unsigned int i=0; i<recentLogs.size(); i++)
  {
    auto data = recentLogs[i];
    //do entry actions
    if (data.receiver->getIsAlive())
    {
      int beginHP = data.receiver->getHealth();
      applyLog(recentLogs[i]);
      addBacklog(data, beginHP);
    }
  }
  recentLogs.clear();
}

void CombatTracker::applyLog(CombatLog& data)
{
  int beginHP = data.receiver->getHealth();
  int maxHP = data.receiver->getMaxHealth();
  int minHP = 0;

  switch (data.entryType)
  {
    case ENTRY_TYPE_DAMAGE :
    {
      //todo: take into account modifiers
      int endHP = beginHP - data.amount;
      endHP = FMath::clampInt(endHP, minHP, maxHP);
      data.receiver->setHealth(endHP);
      //dodo: receiver was killed
      if (endHP == 0)
      {
        
      }
      break;
    }
    case ENTRY_TYPE_HEAL :
    {
      //todo: take into account modifiers
      int endHP = beginHP + data.amount;
      endHP = FMath::clampInt(endHP, minHP, maxHP);
      data.receiver->setHealth(endHP);
      //dodo: receiver was killed
      if (endHP == 0)
      {

      }

      break;
    }
    default: {}
  }
}

void CombatTracker::addBacklog(CombatLog& data, int beginHP)
{
  //remove oldest backlog entry if max size has been reached
  if (backlog.size() >= BACKLOG_MAXSIZE)
  {
    backlog.erase(backlog.begin());
  }

  int endHP = data.receiver->getHealth();
  int diff = abs(beginHP - endHP);

  backlog.push_back({
    data.giver->getName(),
    data.receiver->getName(),
    data.ability->getName(),
    diff,
    data.entryType,
    beginHP,
    endHP,
    Time::getGameTime()
  });
}