#ifndef UNIT_H
#define UNIT_H

#include <oak/ecs/component.h>
#include <vector>
#include <string>
#include <oak/ability/ability.h>

namespace oak
{
  class Unit : public Component
  {
    int health = 100;
    int mana = 100;
    int maxMana = 100;
    int maxHealth = 100;
    int level = 1;
    int startingLevel = 1;
    bool isAlive = true;

    std::string name;

    std::vector<Ability*> abilitys;

  public:
    Unit(const std::string& name);
    ~Unit();

    void onCreate() override;
    void onTick() override;

    bool getIsAlive() const;
    int getHealth() const;
    int getMaxHealth() const;
    int getMaxMana() const;
    int getMana() const;
    int getLevel() const;
    const std::string& getName() const;

    void setMaxHealth(const int maxHealth);
    void setMaxMana(const int maxMana);
    void setStartingLevel(int level);

    
  };
}

#endif
