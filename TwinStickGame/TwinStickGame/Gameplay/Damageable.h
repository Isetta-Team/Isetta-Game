/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include <IsettaEngine.h>

using namespace Isetta;

DEFINE_COMPONENT(Damageable, Component, true)
public:
Delegate<int> deathDelegate{};
Delegate<int> damageDelegate{};

explicit Damageable(const int maxHealth)
    : health{maxHealth}, maxHealth{maxHealth} {}

void DealDamage(int playerIndex, int damage);

int GetHealth() const { return health; }
int GetMaxHealth() const { return maxHealth; }

private:
int health, maxHealth;
bool isDead{false};
DEFINE_COMPONENT_END(Damageable, Component)