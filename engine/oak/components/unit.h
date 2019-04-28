#pragma once
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

    uchar ABILITY_STATE_NONE = 0;
    uchar ABILITY_STATE_PRECAST = 1;
    uchar ABILITY_STATE_CASTING = 2;

    static const char CASTING_STATE_NONE = 0;
    static const char CASTING_STATE_PRECAST = 1;
    static const char CASTING_STATE_CASTING = 2;

    char castingState = CASTING_STATE_NONE;

    Ability* curAbilityCasting = nullptr;
    float spellStartTime = -200.0f;
    float spellEndTime = -200.0f;

  public:
    Unit(const std::string& name);
    ~Unit();

    void onCreate() override;
    void onTick() override;

    void updateCastingState();

    bool getIsAlive() const;
    int getHealth() const;
    int getMaxHealth() const;
    int getMaxMana() const;
    int getMana() const;
    int getLevel() const;
    const std::string& getName() const;

    void setMana(const int mana);
    void setHealth(const int health);

    void giveMana(const int amount);

    void setMaxHealth(const int maxHealth);
    void setMaxMana(const int maxMana);
    void setStartingLevel(int level);

    void castAbility(const uint index);
    uint getAbilityCount() const;

    void addAbility(Ability* ability);
  };
}

#endif
