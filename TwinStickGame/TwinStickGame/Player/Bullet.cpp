/*
 * Copyright (c) 2018 Isetta
 */
#include "Bullet.h"
#include <Core/IsettaCore.h>

using namespace Isetta;

void Bullet::Initialize(const Math::Vector3& pos, const Math::Vector3& dir) {
  transform->LookAt(dir);
  transform->SetWorldPos(pos);
  this->dir = dir;
}

void Bullet::Update() {
  transform->TranslateWorld(dir * speed * Time::GetDeltaTime());
}
