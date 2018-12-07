/*
 * Copyright (c) 2018 Isetta
 */
#include <IsettaEngine.h>

#include "Bullet.h"

using namespace Isetta;

void Bullet::Initialize(const Math::Vector3& pos, const Math::Vector3& dir,
                        const float speed, const float range) {
  transform->LookAt(dir);
  transform->SetWorldPos(pos);
  this->dir = dir;
  this->speed = speed;
  lifeTime = range / speed;
}

void Bullet::Update() {
  transform->TranslateWorld(dir * speed * Time::GetDeltaTime());
  elapsedTime += Time::GetDeltaTime();
  if (elapsedTime >= lifeTime) {
    // TODO(YIDI): Destroy this
    Entity::Destroy(entity);
  }
}
