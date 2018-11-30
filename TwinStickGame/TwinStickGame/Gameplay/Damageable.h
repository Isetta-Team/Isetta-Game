/*
 * Copyright (c) 2018 Isetta
 */
#pragma once
#include "Scene/Component.h"

using namespace Isetta;

DEFINE_COMPONENT(Damageable, Component, true)
private:
int health, maxHealth;

public:
Damageable(int maxHealth) : maxHealth{maxHealth}, health{maxHealth} {}

void DealDamage(int dealDmg);

inline int GetHealth() const { return health; }
inline int GetMaxHealth() const { return maxHealth; }
DEFINE_COMPONENT_END(Damageable, Component)