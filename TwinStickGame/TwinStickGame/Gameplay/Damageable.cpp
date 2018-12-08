/*
 * Copyright (c) 2018 Isetta
 */
#include <IsettaEngine.h>

#include "Damageable.h"

using namespace Isetta;

void Damageable::DealDamage(const int playerIndex, const int damage) {
  if (isDead) return;

  health -= damage;
  if (health < 0) {
    health = 0;
    isDead = true;
    deathDelegate.Invoke(playerIndex);
  }
  damageDelegate.Invoke(playerIndex);
}

void Damageable::Reset() {
  health = maxHealth;
  isDead = false;
}
