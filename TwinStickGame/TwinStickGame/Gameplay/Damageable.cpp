/*
 * Copyright (c) 2018 Isetta
 */
#include "Damageable.h"

// ENGINE
#include "Events/EventObject.h"
#include "Events/Events.h"
#include "Scene/Entity.h"

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
