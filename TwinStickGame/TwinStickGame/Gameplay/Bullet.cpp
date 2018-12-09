/*
 * Copyright (c) 2018 Isetta
 */
#include <IsettaEngine.h>

#include "Bullet.h"

using namespace Isetta;

void Bullet::Shoot(const Math::Vector3& pos, const Math::Vector3& dir,
                   const float speed) {
  transform->LookAt(transform->GetWorldPos() + dir);
  transform->SetWorldPos(pos);
  this->dir = dir;
  this->speed = speed;
}

void Bullet::Update() {
  transform->TranslateWorld(dir * speed * Time::GetDeltaTime());
}