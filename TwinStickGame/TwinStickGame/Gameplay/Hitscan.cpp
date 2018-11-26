/*
 * Copyright (c) 2018 Isetta
 */
#include "Gameplay/Hitscan.h"
#include "Collisions/Collider.h"
#include "Collisions/Collisions.h"
#include "Collisions/RaycastHit.h"
#include "Core/IsettaCore.h"
#include "Gameplay/Damageable.h"
#include "brofiler/ProfilerCore/Brofiler.h"

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

  Array<RaycastHit> hits;
  auto it = shots.begin();
  while (it != shots.end()) {
    // Draw the ray
#ifdef _EDITOR
    DebugDraw::Line(
        it->ray.GetOrigin() + it->ray.GetDirection() * it->travel,
        it->ray.GetOrigin() + it->ray.GetDirection() *
                                  (it->travel + it->props->speed * deltaTime),
        Color::red, 5);
#endif

    // If the ray hits at the appropriate range, it's a hit
    float closestDist = INFINITY;
    RaycastHit* closestHit = nullptr;
    hits = Collisions::RaycastAll(
        it->ray, it->travel + it->props->speed * deltaTime);
    for (auto& hit : hits) {
      if (hit.GetDistance() - it->travel >= 0 &&
          hit.GetDistance() - it->travel < closestDist) {
        closestDist = hit.GetDistance() - it->travel;
        closestHit = &hit;
      }
    }

    if (closestHit) {
      Damageable* damageable =
          closestHit->GetCollider()->entity->GetComponent<Damageable>();
      if (damageable) {
        damageable->DealDamage(it->props->damage);
      }

      // Draw the collision
#ifdef _EDITOR
      DebugDraw::Point(closestHit->GetPoint(), Color::white, 5, .5);
#endif

      if (!it->props->piercing) {
        --it->props->refCount;
        it = shots.erase(it);
        continue;
      }
    }

    it->travel += it->props->speed * deltaTime;
    if (it->travel > it->props->range) {
      --it->props->refCount;
      it = shots.erase(it);
    } else {
      ++it;
    }

    hits.Clear();
  }

  // Clear out all of the unused properties objects
  shotProps.remove_if([](HitscanProps props) { return props.refCount <= 0; });
}

void Hitscan::Fire(Math::Vector3 origin, Math::Vector3 direction) {
  if (cooldownTimer <= 0) {
    // Generate the shot
    Ray ray(origin, direction);
    HitscanShot& shot = shots.emplace_back(ray);

    // Connect the shot properties to the shot
    if (propertiesChanged || shotProps.size() == 0) {
      shot.props = &shotProps.emplace_back(properties);
      propertiesChanged = false;
    } else {
      shot.props = &shotProps.back();
    }
    ++shot.props->refCount;

    // Reset the cooldown
    cooldownTimer = cooldown;
  }
}

int Hitscan::GetNumFired() { return shots.size(); }
int Hitscan::GetNumProps() { return shotProps.size(); }

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