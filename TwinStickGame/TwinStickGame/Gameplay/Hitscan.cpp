/*
 * Copyright (c) 2018 Isetta
 */
#include "Gameplay/Hitscan.h"
#include <IsettaEngine.h>
#include "Gameplay/Damageable.h"

Hitscan::Hitscan(const float range, const float speed, const int damage) {
  properties.range = range;
  properties.speed = speed;
  properties.damage = damage;
}

void Hitscan::Update() {
  float deltaTime = Time::GetDeltaTime();

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

    // Move bullets
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
}

int Hitscan::GetNumFired() const { return bullets.size(); }
int Hitscan::GetNumProps() const { return bulletProps.size(); }

float Hitscan::GetRange() const { return properties.range; }
void Hitscan::SetRange(const float range) {
  properties.range = range;
  propertiesChanged = true;
}
float Hitscan::GetSpeed() const { return properties.speed; }
void Hitscan::SetSpeed(const float speed) {
  properties.speed = speed;
  propertiesChanged = true;
}
int Hitscan::GetDamage() const { return properties.damage; }
void Hitscan::SetDamage(const int damage) {
  properties.damage = damage;
  propertiesChanged = true;
}
bool Hitscan::GetPiercing() const { return properties.piercing; }
void Hitscan::SetPiercing(const bool shouldPierce) {
  properties.piercing = shouldPierce;
  propertiesChanged = true;
}

HitscanBullet::HitscanBullet(Ray inRay) : ray{inRay} {}

bool HitscanBullet::operator==(const HitscanBullet& rhs) const {
  return ray.GetDirection() == rhs.ray.GetDirection() &&
         ray.GetOrigin() == rhs.ray.GetOrigin() && travel == rhs.travel;
}
