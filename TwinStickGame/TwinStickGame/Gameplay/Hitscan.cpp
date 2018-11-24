/*
 * Copyright (c) 2018 Isetta
 */
#include "Gameplay/Hitscan.h"
#include "Collisions/Collider.h"
#include "Collisions/Collisions.h"
#include "Collisions/RaycastHit.h"
#include "Core/IsettaCore.h"
#include "Gameplay/Damageable.h"

Hitscan::Hitscan(float range, float rate, float speed, int damage) {
  properties.range = range;
  cooldown = 1.f / rate;
  properties.speed = speed;
  properties.damage = damage;
}

void Hitscan::Update() {
  float deltaTime = Time::GetDeltaTime();
  cooldownTimer =
      Math::Util::Max(0, cooldownTimer - deltaTime);  // Gotta avoid underflow

  RaycastHit hit;
  for (auto& shot : shots) {
    if (Collisions::Raycast(shot.ray, &hit, shot.props->range) &&
        hit.GetDistance() - shot.travel < shot.props->speed * deltaTime) {
      shots.remove(shot);

      Damageable* damageable =
          hit.GetCollider()->entity->GetComponent<Damageable>();
      if (damageable) {
        damageable->DealDamage(shot.props->damage);
      }
    }

#ifdef _DEBUG
    DebugDraw::Line(
        shot.ray.GetOrigin() + shot.ray.GetDirection() * shot.travel,
        shot.ray.GetOrigin() +
            shot.ray.GetDirection() * (shot.travel + shot.props->speed),
        Color::red);
#endif

    shot.travel += shot.props->speed * deltaTime;
    if (shot.travel > shot.props->range) {
      shots.remove(shot);
    }
  }
}

void Hitscan::Fire(Math::Vector3 origin, Math::Vector3 direction) {
  if (cooldownTimer <= 0) {
    // Generate the shot
    Ray ray(origin, direction);
    HitscanShot shot = shots.emplace_back(ray);

    // Connect the shot properties to the shot
    HitscanProps* props;
    if (propertiesHaveChanged) {
      props = &shotProps.emplace_back(properties);
      propsReferenceCounts[props] = 0;
    } else {
      props = &shotProps.back();
    }
    ++propsReferenceCounts[props];

    // Reset the cooldown
    cooldownTimer = cooldown;
  }
}

HitscanShot::HitscanShot(Ray inRay) : ray{inRay} {}

bool HitscanShot::operator==(const HitscanShot& rhs) {
  return ray.GetDirection() == rhs.ray.GetDirection() &&
         ray.GetOrigin() == rhs.ray.GetOrigin() && travel == rhs.travel;
}