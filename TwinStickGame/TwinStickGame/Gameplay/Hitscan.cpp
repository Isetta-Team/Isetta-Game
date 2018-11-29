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

  Ray bullet = Ray(Math::Vector3::zero, Math::Vector3::forward);
  auto it = bullets.begin();
  while (it != bullets.end()) {
    bullet.SetOrigin(it->ray.GetOrigin() + it->ray.GetDirection() * it->travel);
    bullet.SetDirection(it->ray.GetDirection());

    // Draw the ray
#ifdef _EDITOR
    DebugDraw::Line(
        it->ray.GetOrigin() + it->ray.GetDirection() * it->travel,
        it->ray.GetOrigin() + it->ray.GetDirection() *
                                  (it->travel + it->props->speed * deltaTime),
        Color::red, 5);
#endif

    // If the ray hits at the appropriate range, it's a hit
    RaycastHit hit;
    if (Collisions::Raycast(bullet, &hit, it->props->speed * deltaTime)) {
      Damageable* damageable =
          hit.GetCollider()->entity->GetComponent<Damageable>();
      if (damageable) {
        damageable->DealDamage(it->props->damage);
      }

      // Draw the collision
#ifdef _EDITOR
      DebugDraw::Point(hit.GetPoint(), Color::white, 5, .5);
#endif

      if (!it->props->piercing) {
        --it->props->refCount;
        it = bullets.erase(it);
        continue;
      }
    }

    it->travel += it->props->speed * deltaTime;
    if (it->travel > it->props->range) {
      --it->props->refCount;
      it = bullets.erase(it);
    } else {
      ++it;
    }
  }
}

void Hitscan::Fire(Math::Vector3 origin, Math::Vector3 direction) {
  if (cooldownTimer <= 0) {
    // Generate the bullet
    Ray ray(origin, direction);
    HitscanBullet& bullet = bullets.emplace_back(ray);

    // Connect the bullet properties to the bullet
    if (propertiesChanged || bulletProps.size() == 0) {
      bullet.props = &bulletProps.emplace_back(properties);
      propertiesChanged = false;
    } else {
      bullet.props = &bulletProps.back();
    }
    ++bullet.props->refCount;

    // Reset the cooldown
    cooldownTimer = cooldown;
  }
}

int Hitscan::GetNumFired() { return bullets.size(); }
int Hitscan::GetNumProps() { return bulletProps.size(); }

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

HitscanBullet::HitscanBullet(Ray inRay) : ray{inRay} {}

bool HitscanBullet::operator==(const HitscanBullet& rhs) {
  return ray.GetDirection() == rhs.ray.GetDirection() &&
         ray.GetOrigin() == rhs.ray.GetOrigin() && travel == rhs.travel;
}