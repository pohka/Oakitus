#ifndef UNIT_H
#define UNIT_H

#include <oak/ecs/component.h>
#include <vector>
#include <string>

namespace oak
{
  class Unit : public Component
  {
    float health = 100.0f;
    float mana = 100.0f;
    float maxMana = 100.0f;
    float maxHealth = 100.0f;
    int level = 1;
    int startingLevel = 1;
    bool isAlive = true;

    std::string name;

    //std::vector<Ability> abilitys;

  public:
    Unit(const std::string& name);
    ~Unit();

    void onCreate() override;
    void onTick() override;

    bool getIsAlive() const;
    float getHealth() const;
    float getMaxHealth() const;
    float getMaxMana() const;
    float getMana() const;
    int getLevel() const;
    const std::string& getName() const;

    void setMaxHealth(float maxHealth);
    void setMaxMana(float maxMana);
    void setStartingLevel(int level);

    
  };
}

#endif
