/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include <IsettaEngine.h>

using namespace Isetta;

DEFINE_COMPONENT(Damageable, Component, true)
public:
Delegate<> deathDelegate{};
Delegate<> damageDelegate{};

explicit Damageable(const int maxHealth)
    : health{maxHealth}, maxHealth{maxHealth} {}

void DealDamage(int damage);

int GetHealth() const { return health; }
int GetMaxHealth() const { return maxHealth; }

private:
int health, maxHealth;
bool isDead{false};
DEFINE_COMPONENT_END(Damageable, Component)