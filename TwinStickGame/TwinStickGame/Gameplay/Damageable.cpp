/*
 * Copyright (c) 2018 Isetta
 */
#include <IsettaEngine.h>
#include "Damageable.h"

using namespace Isetta;

void Damageable::DealDamage(int dealDmg) {
  // TODO(Jacob) change name to id
  health -= dealDmg;
  if (health < 0) {
    health = 0;
    Events::Instance().RaiseImmediateEvent(
        {"DeathEvent", {entity->GetName(), health, dealDmg}});
  }
  Events::Instance().RaiseImmediateEvent(
      {"DamageEvent", {entity->GetName(), health, dealDmg}});
}
