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
#ifdef _DEBUG
  DebugDraw::Point(Math::Vector3::zero, Color::blue, 8);
#endif
  float deltaTime = Time::GetDeltaTime();
  cooldownTimer =
      Math::Util::Max(0, cooldownTimer - deltaTime);  // Gotta avoid underflow

  RaycastHit hit;
  auto it = shots.begin();
  while (it != shots.end()) {
#ifdef _DEBUG
    DebugDraw::Line(
        it->ray.GetOrigin() + it->ray.GetDirection() * it->travel,
        it->ray.GetOrigin() + it->ray.GetDirection() *
                                  (it->travel + it->props->speed * deltaTime),
        Color::red, 5);
#endif
    if (Collisions::Raycast(it->ray, &hit, it->props->range) &&
        hit.GetDistance() - it->travel < it->props->speed * deltaTime) {
      if (!it->props->piercing) it = shots.erase(it);

      Damageable* damageable =
          hit.GetCollider()->entity->GetComponent<Damageable>();
      if (damageable) {
        damageable->DealDamage(it->props->damage);
      }
#ifdef _DEBUG
      DebugDraw::Point(hit.GetPoint(), Color::white, 5, .5);
#endif
    } else {
      it->travel += it->props->speed * deltaTime;
      if (it->travel > it->props->range) {
        it = shots.erase(it);
      } else {
        ++it;
      }
    }
  }
}

void Hitscan::Fire(Math::Vector3 origin, Math::Vector3 direction) {
  if (cooldownTimer <= 0) {
    // Generate the shot
    Ray ray(origin, direction);
    HitscanShot& shot = shots.emplace_back(ray);

    // Connect the shot properties to the shot
    if (propertiesChanged) {
      shot.props = &shotProps.emplace_back(properties);
      propsReferenceCounts[shot.props] = 0;
      propertiesChanged = false;
    } else {
      shot.props = &shotProps.back();
    }
    ++propsReferenceCounts[shot.props];

    // Reset the cooldown
    cooldownTimer = cooldown;
  }
}

float Hitscan::GetRange() { return properties.range; }
void Hitscan::SetRange(float r) {
  properties.range = r;
  propertiesChanged = true;
}
float Hitscan::GetSpeed() { return properties.speed; }
void Hitscan::SetSpeed(float s) {
  properties.speed = s;
  propertiesChanged = true;
}
int Hitscan::GetDamage() { return properties.damage; }
void Hitscan::SetDamage(int d) {
  properties.damage = d;
  propertiesChanged = true;
}
bool Hitscan::GetPiercing() { return properties.piercing; }
void Hitscan::SetPiercing(bool p) {
  properties.piercing = p;
  propertiesChanged = true;
}

HitscanShot::HitscanShot(Ray inRay) : ray{inRay} {}

bool HitscanShot::operator==(const HitscanShot& rhs) {
  return ray.GetDirection() == rhs.ray.GetDirection() &&
         ray.GetOrigin() == rhs.ray.GetOrigin() && travel == rhs.travel;
}